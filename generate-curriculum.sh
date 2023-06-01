#!/bin/bash

# This script can be used to generate a SYCL curriculum from some subset of
# all of the chapters in SYCLacademy. The usage is best explained in the usage()
# func.

usage() {
  echo "Usage: ./generate-curriculum.sh [OPTIONS] [CHAPTERS]"
  echo "This script generates a curriculum of SYCLAcademy using all of the"
  echo "chapters that are listed as args"
  echo
  echo "Options:"
  echo "  -h, --help          Show this help message and exit."
  echo "  -e, --exclude-deps  Exclude dependent chapters"
  echo
  echo "Arguments:"
  echo "  CHAPTERS Any integers between 1 and $maxChapter inclusive."
  echo
  echo "Example:"
  echo "   ./generate-curriculum.sh 2 4 18 7"
  echo "   Will generate a 4 chapter curriculum, numbered from 1-4 where"
  echo "   chapter 1 corresponds to chapter 2 from main"
  echo "   chapter 2 corresponds to chapter 4 from main"
  echo "   chapter 3 corresponds to chapter 18 from main"
  echo "   chapter 4 corresponds to chapter 7 from main"
  echo
  echo "The default behaviour is for a curriculum to be built with"
  echo "dependencies. So if chapter 18 depends on chapter 15, the built"
  echo "curriculum will instead be:"
  echo
  echo "   ./generate-curriculum.sh 2 4 18 7"
  echo "   Will generate a 5 chapter curriculum, numbered from 1-5 where"
  echo "   chapter 1 corresponds to chapter 2 from main"
  echo "   chapter 2 corresponds to chapter 4 from main"
  echo "   chapter 3 corresponds to chapter 15 from main"
  echo "   chapter 4 corresponds to chapter 18 from main"
  echo "   chapter 5 corresponds to chapter 7 from main"
  echo
  echo "Dependencies are defined in Lesson_Materials/Lecture_*/DEPS.txt and"
  echo "can be omitted using the "-e" flag."
  exit 0
}

getValidChapters() {
  for ((i=1; i<=maxChapter; i++)); do
    if [[ $i -lt 10 ]]; then
      validChapters+=("0$i")
    else
      validChapters+=("$i")
    fi
  done

  # Add some lecture only sections
  validChapters+=("00A")
  validChapters+=("00B")
  validChapters+=("14A")
  validChapters+=("18A")
  validChapters+=("18B")
}

parseArgs() {
  # Iterate over each command line argument
  for arg in "$@"; do
    # Check if argument is an integer and between 1 and maxChapter
    if [[ $arg == '-h' || $arg == '--help' ]]; then
      usage
    fi
    if [[ $arg == '-e' || $arg == '--exclude-deps' ]]; then
      excludeDependencies="true"
    fi

    strArg="$arg"
    # Prepend single digit numbers with 0
    if [[ ${#strArg} -eq 1 ]]; then
      strArg="0$strArg"
    fi

    # Check if arg is a valid chapter
    valid=false
    for validChapter in "${validChapters[@]}"; do
      if [[ "$strArg" == $validChapter ]]; then
        chosenChapters+=($strArg)
        valid=true
        break
      fi
    done

    if [[ ! $valid && $arg != "-e" ]]; then
      echo "Invalid argument: $arg. Chapter should be an integer between 1 and $maxChapter (inclusive)."
    fi
  done
}

# If chapter A depends on chapter B, chapter B will always be before chapter B
# in the curriculum
getDependentChapters() {
  for chapter in ${chosenChapters[@]}; do
    chapterName=$(ls Lesson_Materials | grep "Lecture_${chapter}_")
    if [[ -f Lesson_Materials/$chapterName/DEPS.txt ]]; then
      while IFS= read -r line; do
        dependentChapters+=("$line")
        echo "Chapter $chapter is dependent on chapter $line  => Adding chapter $line to curriculum"
        echo "(Run with flag -e to exclude dependent chapters from curriculum)"
      done < Lesson_Materials/$chapterName/DEPS.txt
    fi
    dependentChapters+=("$chapter")
  done
  chosenChapters=("${dependentChapters[@]}")
  echo
}

getToDeleteChapters() {
  for chapter in ${validChapters[@]}; do
    toDelete=true
    for chosenChapter in ${chosenChapters[@]}; do
      if [[ $chosenChapter == $chapter ]]; then
        toDelete=false
        break
      fi
    done
    if $toDelete; then
      chaptersToDelete+=("$chapter")
    fi
  done
}

if [[ $# -eq 0 ]]; then
  usage
fi

# Get the max chapter value
maxChapter=0
for dir in $(ls Code_Exercises | grep Exercise_*); do
  if [[ $dir =~ Exercise_([0-9]+) ]]; then
    number=${BASH_REMATCH[1]}
    if [[ $number == 0* ]]; then
      number="${number#0}"
    fi
    (( number > max_number )) && maxChapter=$number
  fi
done

validChapters=() # Valid chapters that can be used
chosenChapters=() # Chapters that will be used in curriculum
chaptersToDelete=() # Chapters that will be used in curriculum
dependentChapters=() # Chosen chapters plus dependencies
getValidChapters
parseArgs $@
# Get dep chapters if -e flag not passed
[[ -z $excludeDependencies ]] && getDependentChapters
getToDeleteChapters

for toDelete in ${chaptersToDelete[@]}; do
  # Remove links to old chapters in the README
  sed -i '' "/| $toDelete |/d" README.md
  sed -i '' "/lesson-$toDelete/d" README.md
  sed -i '' "/_${toDelete}_/d" Code_Exercises/CMakeLists.txt

  # Delete unused sections
  rm -fr Code_Exercises/*_${toDelete}_*
  rm -fr Lesson_Materials/*_${toDelete}_*
done

for ((i=0; i<${#chosenChapters[@]}; i++)); do
  if [[ $i -lt 9 ]]; then
    strNewSectionNum=("0$(($i+1))")
  else
    strNewSectionNum=("$((i+1))")
  fi

  # Renumber Code Exercises
  cd Code_Exercises
  codeDirToMove=$(ls | grep "_${chosenChapters[$i]}_")
  if [[ -n $codeDirToMove ]]; then
    newCodeDirName=$(echo $codeDirToMove | sed "s/${chosenChapters[$i]}/${strNewSectionNum}/g")
    if [[ -n $(ls | grep $codeDirToMove) ]]; then
      mv $codeDirToMove $newCodeDirName
      sed -i '' "s/${chosenChapters[$i]}/${strNewSectionNum}/g" $newCodeDirName/README.md
      sed -i '' "s/${chosenChapters[$i]}/${strNewSectionNum}/g" $newCodeDirName/CMakeLists.txt
    fi
  fi

  # Renumber Lesson Materials
  cd ../Lesson_Materials
  lessonDirToMove=$(ls | grep "_${chosenChapters[$i]}_")
  if [[ -n $lessonDirToMove ]]; then
    newLessonDirName=$(echo $lessonDirToMove | sed "s/${chosenChapters[$i]}/${strNewSectionNum}/g")
    if [[ -n $(ls | grep $lessonDirToMove) ]]; then
      mv $lessonDirToMove $newLessonDirName
      [[ -f $newLessonDirName/$lessonDirToMove.pdf ]] && mv $newLessonDirName/$lessonDirToMove.pdf $newLessonDirName/$newLessonDirName.pdf
      [[ -f $newLessonDirName/index.html ]] && sed -i '' "s/${chosenChapters[$i]}/${strNewSectionNum}/g" $newLessonDirName/index.html
    fi
  fi
  cd ..

  # Update the links to the new chapter numbers in README and CMakeLists.txt
  sed -i '' "s/_${chosenChapters[$i]}_/_${strNewSectionNum}_/g" README.md
  sed -i '' "s/| ${chosenChapters[$i]} |/| ${strNewSectionNum} |/g" README.md
  sed -i '' "s/_${chosenChapters[$i]}_/_${strNewSectionNum}_/g" Code_Exercises/CMakeLists.txt

done

echo "Have generated curriculum with"
echo
echo "Code exercises:"
echo "$(ls Code_Exercises | grep Exercise)"
echo
echo "Lesson materials:"
echo "$(ls Lesson_Materials | grep Lecture)"

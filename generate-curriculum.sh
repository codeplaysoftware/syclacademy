#!/bin/bash

# TODO this bash script calls `sed` in the linux way, not compatible with the
# macOS usage. Add a wrapper func to make a cross platform sed.

# TODO The index of chapters does not reorder chapters, if needed. Automate this

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
  echo "  CHAPTERS: A list of chapter names, as spelled in Lesson_Materials."
  echo
  echo "Example:"
  echo "   ./generate-curriculum.sh Why_Parallel_and_Heterogeneous Managing_Data Data_Parallelism"
  echo "   Will generate a 3 chapter curriculum, numbered from 1-3 where"
  echo "   chapter 1 corresponds to Why_Parallel_and_Heterogeneous from main"
  echo "   chapter 2 corresponds to Managing_Data from main"
  echo "   chapter 3 corresponds to Data_Parallelism from main"
  echo
  echo "The default behaviour is for a curriculum to be built with"
  echo "dependencies. So if chapter 18 depends on chapter 15, the built"
  echo "curriculum will instead be:"
  echo
  echo "   ./generate-curriculum.sh Why_Parallel_and_Heterogeneous Managing_Data Vectors"
  echo "   Will generate a 4 chapter curriculum, numbered from 1-3 where"
  echo "   chapter 1 corresponds to Why_Parallel_and_Heterogeneous from main"
  echo "   chapter 2 corresponds to Managing_Data from main"
  echo "   chapter 3 corresponds to Image_Convolution from main"
  echo "            (Defined as a DEP of Vectors)"
  echo "   chapter 4 corresponds to Vectors from main"
  echo
  echo "Dependencies are defined in Lesson_Materials/*/DEPS.txt and"
  echo "can be omitted using the "-e" flag."
  exit 0
}

getValidChapters() {
  validChapters=($(ls Lesson_Materials | grep -v common-revealjs))
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
    valid="false"
    for validChapter in "${validChapters[@]}"; do
      if [[ "$strArg" == $validChapter ]]; then
        chosenChapters+=($strArg)
        valid="true"
        break
      fi
    done

    if [[ $valid == "false" && $arg != "-e" ]]; then
      echo "Invalid argument: $arg. Chapter should be a directory in Lesson_Materials."
      exit 1
    fi
  done
}

# If chapter A depends on chapter B, chapter B will always be before chapter B
# in the curriculum
getDependentChapters() {
  for chapter in ${chosenChapters[@]}; do
    if [[ -f Lesson_Materials/$chapter/DEPS.txt ]]; then
      while IFS= read -r line; do
        dependentChapters+=("$line")
        echo "Chapter $chapter is dependent on chapter $line  => Adding chapter $line to curriculum"
        echo "(Run with flag -e to exclude dependent chapters from curriculum)"
      done < Lesson_Materials/$chapter/DEPS.txt
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

validChapters=() # Valid chapters that can be used
chosenChapters=() # Chapters that will be used in curriculum
chaptersToDelete=() # Chapters that will be used in curriculum
dependentChapters=() # Chosen chapters plus dependencies

getValidChapters
parseArgs $@
# Get dep chapters if -e flag not passed
[[ -z $excludeDependencies ]] && getDependentChapters
getToDeleteChapters
echo "Have ${#chaptersToDelete[@]} chapters to delete"

for toDelete in ${chaptersToDelete[@]}; do
  # Swap underscores for spaces
  toDeleteNoUnderscores="${toDelete//_/ }"
  echo $toDeleteNoUnderscores
  # Remove links to old chapters in the README
  sed -i "/| $toDeleteNoUnderscores |/d" README.md
  sed -i "s/| [0-9][0-9]/| /g" README.md
  sed -i "/${toDelete}/d" Code_Exercises/CMakeLists.txt

  if [[ $toDelete != "common-revealjs" ]]; then
    # Delete unused sections
    rm -fr Code_Exercises/${toDelete}
    rm -fr Lesson_Materials/${toDelete}
  fi
done

for ((i=0; i<${#chosenChapters[@]}; i++)); do
  newSectionDirName="Section_$((i+1))_${chosenChapters[$i]}"
  # Number Code Exercises
  cd Code_Exercises
  if [[ -d ${chosenChapters[$i]} ]]; then
    mv ${chosenChapters[$i]} $newSectionDirName
    sed -i "s/${chosenChapters[$i]}/${newSectionDirName}/g" $newSectionDirName/README.md $newSectionDirName/CMakeLists.txt CMakeLists.txt
  fi

  # Number Lesson Materials
  cd ../Lesson_Materials
  if [[ -d ${chosenChapters[$i]} ]]; then
    mv ${chosenChapters[$i]} $newSectionDirName
    [[ -f $newSectionDirName/$lessonSectionToMove.pdf ]] && mv $newSectionDirName/$newSectionDirName.pdf $newSectionDirName/$newSectionDirName.pdf
    [[ -f $newSectionDirName/index.html ]] && sed -i "s/${chosenChapters[$i]}/${newSectionDirName}/g" $newSectionDirName/index.html
  fi
  cd ..

  # Update the links to the new chapter numbers in README and CMakeLists.txt
  sed -i "s/${chosenChapters[$i]}/${newSectionDirName}/g" README.md
done

echo "Have generated curriculum with"
echo
echo "Code exercises:"
echo "==============="
echo
echo "$(ls Code_Exercises | grep Section | sort)"
echo
echo "Lesson materials:"
echo "================="
echo
echo "$(ls Lesson_Materials | grep Section | sort )"

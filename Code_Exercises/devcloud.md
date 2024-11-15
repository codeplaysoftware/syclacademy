### Setting up Tiber Cloud

If you have not done so already, follow the instructions in the [README](../README.md#get-started-working-on-the-exercises-on-intel-tiber-cloud) to set up your environment.

### Building the Exercises

It is possible to compile single source files using a single simple command.

`icpx -fsycl -o exercise-x.out source.cpp`

The source.cpp file is the one you want to compile.
The -o output is the binary you can then run on the machine e.g.

`./exercise-x.out`

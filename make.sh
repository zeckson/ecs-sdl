#!/bin/sh
set -eo pipefail
IFS=$'\n\t'

PROFILE="debug"
PROJECT_NAME="ECSSDL2"

# Function to clean the build directory
clean() {
    echo "Cleaning build directory..."
    cmake --build build/$PROFILE --target clean -j 6
}

# Function to configure and build the project
build() {
    echo "Configuring and building project..."
    cmake --build build/$PROFILE --target $PROJECT_NAME -j 6
}

# Function to run CTest
test() {
    echo "Running tests..."
    cd build/$PROFILE || exit
    ctest
}

# Function to run the project
run() {
    echo "Running the project..."
    ./build/$PROFILE/$PROJECT_NAME
}

# Display usage information
usage() {
    echo "Usage: $0 {clean|build|test|run}"
    exit 1
}

# Main function
main() {
    case "$1" in
        clean)
            clean
            ;;
        build)
            build
            ;;
        test)
            test
            ;;
        run)
            run
            ;;
        *)
            usage
            ;;
    esac
}

# Execute the main function with command-line arguments
main "$@"

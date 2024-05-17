#!/bin/bash

# Define source file patterns
SOURCES=(
    "src/*.c"
    "src/entity/*.c"
    "src/render/*.c"
    "src/map/*.c"
    "src/utils/*.c"
)

# Define flags
FLAGS="-lraylib -lm"

OS="$1" # linux or win (first argument)

if [ "$OS" == "win" ]; then
    # Define directories
    INCLUDE_DIR="/usr/local/include"
    LIBRARY_DIR="./lib"
    echo "Compiling for Windows"
    
    # Define output and compiler
    OUTPUT="./lib/DungeonDelveC.exe"
    COMPILER="x86_64-w64-mingw32-gcc"

elif [ "$OS" == "linux" ] || [ "$OS" == "" ]; then
    # Define directories
    INCLUDE_DIR="/usr/local/include"
    LIBRARY_DIR="/usr/local/lib"
    echo "Compiling for Linux"
    
    # Define output and compiler
    OUTPUT="./lib/DungeonDelveC"
    COMPILER="gcc"
fi

# Clear terminal
clear

# Remove the old binary
rm $OUTPUT || echo "Error removing $OUTPUT"

# Compile the program
$COMPILER -I$INCLUDE_DIR -L$LIBRARY_DIR -o $OUTPUT ${SOURCES[@]} $FLAGS
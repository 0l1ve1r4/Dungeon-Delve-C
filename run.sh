#!/bin/bash

clear

OS="${1:-linux}"                            # Get first argument or default to "linux"
INSTALL="${2}"                              # Get second argument 
                                            #(to check if you already want to install the game) (windows only)

SOURCES=(                                   # Source files  
    "src/*.c"                               # Define them from the "leaf file"                    
    "src/entity/*.c"                        # to the "root file" to avoid
    "src/render/*.c"                        # recompiling all files every time
    "src/map/*.c"                           #
    "src/utils/*.c"                         #
)


FLAGS="-lraylib -lm"                        # raylib library
INCLUDE_DIR="/usr/local/include"            # raylib headers



case "$OS" in
    
    "win") 
        LIBRARY_DIR="./lib"                 # raylib.dll
        OUTPUT="./DungeonDelveC.exe"        # Output file (executable)
        COMPILER="x86_64-w64-mingw32-gcc"   # sudo apt-get install mingw-w64s
        ;;

    "linux") 
        LIBRARY_DIR="/usr/local/lib"        # libraylib.a
        OUTPUT="./DungeonDelveC"
        COMPILER="gcc"
        ;;
    *)
        echo "Invalid OS. Please specify 'win' or 'linux'."
        exit 1
        ;;
esac


rm -f $OUTPUT || echo "Error removing $OUTPUT, but it's okay."


$COMPILER -I$INCLUDE_DIR -L$LIBRARY_DIR -o $OUTPUT ${SOURCES[@]} $FLAGS

echo "Compilation successful."

if [ "$INSTALL" == "install" ]; then

    echo "Installing..."
    
    rm -rf ../build 2&>/dev/null
    mkdir ../build

    if [ "$OS" == "win" ]; then
        cp $LIBRARY_DIR/raylib.dll ../build
    fi

    cp -r res/ ../build

    cp $OUTPUT ../build

    ### Clean up not used files

    rm -f $OUTPUT
    rm -rf ../build/res/readme

    echo "Installed successfully for $OS."
    echo "Build created at" && cd ../build && pwd

fi

if [[ "$OS" == "linux" && "$INSTALL" == "install" ]]; then # This is just to easy the testing process
    echo "Running..."
    ../build/DungeonDelveC 
fi
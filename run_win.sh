ENTITIES="src/entity/*.c"
RENDER="src/render/*.c"
UTILS="src/utils/*.c"
MAIN="src/main.c"

OUTPUT="DungeonDelveC.exe"
COMPILER="x86_64-w64-mingw32-gcc"

RAYLIB_HEADER="/usr/local/include/raylib.h"
RAYLIB_LIB_DIR="/usr/local/lib/libraylib.a"

INCLUDE_DIRS="-I$RAYLIB_INCLUDE_DIR"
LIBRARY_DIRS="-L$RAYLIB_LIB_DIR"
FLAGS="-lraylib -lm"

clear

rm $OUTPUT || echo "Error removing $OUTPUT" # Remove the old binary

$COMPILER -o $OUTPUT $MAIN $UTILS $ENTITIES $RENDER $FLAGS $INCLUDE_DIRS $LIBRARY_DIRS $RAYLIB_HEADER

timeout 50s ./$OUTPUT || echo "Error running $OUTPUT"

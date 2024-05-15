ENTITIES="src/entity/*.c"
RENDER="src/render/*.c"
MAP="src/map/*.c"
UTILS="src/utils/*.c"
MAIN="src/*.c"

OUTPUT="DungeonDelveC"
COMPILER="gcc"

FLAGS="-lraylib -lGL -lm"

clear

rm $OUTPUT || echo "Error removing $OUTPUT" # Remove the old binary

$COMPILER -o $OUTPUT $MAIN $UTILS $ENTITIES $RENDER $MAP $FLAGS 

timeout 60s ./$OUTPUT || echo "Error compiling $OUTPUT"


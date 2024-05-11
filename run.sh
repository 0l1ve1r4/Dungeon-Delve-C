ENTITIES="src/entity/*.c"
RENDER="src/render/*.c"
UTILS="src/utils/*.c"
MAIN="src/main.c"

OUTPUT="DungeonDelveC"
COMPILER="gcc"

FLAGS="-lraylib -lGL -lm -lpthread -ldl -lrt"

clear

rm $OUTPUT || echo "Error removing $OUTPUT" # Remove the old binary

$COMPILER -o $OUTPUT $MAIN $UTILS $ENTITIES $RENDER $FLAGS


timeout 120s ./$OUTPUT || echo "Error running $OUTPUT"


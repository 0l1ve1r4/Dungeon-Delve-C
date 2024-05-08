ENTITIES="src/entity/*.c"
RENDER="src/render/*.c"
MAIN="src/main.c"

OUTPUT="DungeonDelveC"
COMPILER="gcc"

FLAGS="-lraylib -lGL -lm -lpthread -ldl -lrt"

clear

$COMPILER -o $OUTPUT $MAIN $ENTITIES $RENDER $FLAGS


./$OUTPUT || echo "Error running $OUTPUT"

# rm $OUTPUT || echo "Error removing $OUTPUT"
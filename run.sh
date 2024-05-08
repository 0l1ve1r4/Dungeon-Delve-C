ENTITIES="src/entity/*.c"
RENDER="src/render/*.c"
UTILS="src/utils/*.c"
MAIN="src/main.c"

OUTPUT="DungeonDelveC"
COMPILER="gcc"

FLAGS="-lraylib -lGL -lm -lpthread -ldl -lrt"

clear

$COMPILER -o $OUTPUT $MAIN $UTILS $ENTITIES $RENDER $FLAGS


./$OUTPUT || echo "Error running $OUTPUT"

# rm $OUTPUT || echo "Error removing $OUTPUT"
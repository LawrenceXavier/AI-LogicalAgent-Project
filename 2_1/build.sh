SOURCE_PATH="Source"
RELEASE_PATH="Release"

echo "Cleaning all files in $RELEASE_PATH/..."
rm $RELEASE_PATH/*

echo "Compiling Proposition.cpp..."
g++ -std=gnu++14 -c "$SOURCE_PATH/Proposition.cpp" -o "$RELEASE_PATH/Proposition.o"

echo "Compiling Preprocess.cpp..."
g++ -std=gnu++14 -c "$SOURCE_PATH/Preprocess.cpp" -o "$RELEASE_PATH/Preprocess.o"

echo "Compiling main.cpp..."
g++ -std=gnu++14 -c "$SOURCE_PATH/main.cpp" -o "$RELEASE_PATH/main.o"

TEMP_PATH=$PWD

echo "Going to $RELEASE_PATH/"
cd $RELEASE_PATH

echo "Compiling into execute file..."
g++ Proposition.o Preprocess.o main.o -o LogicalAgent

cd "$TEMP_PATH"

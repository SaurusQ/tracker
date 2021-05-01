#!/bin/bash

rm -rf build
mkdir build

find ./general -mindepth 1 -type f -exec cp -t ./build -i '{}' +

if [ $1 == box ];
then
    echo "Compiling box"
    find ./box -mindepth 1 -type f -exec cp -t ./build -i '{}' +
    mv ./build/box.ino ./build/build.ino
    ./arduino-cli compile \
    -p $2 \
    -b esp32:esp32:esp32 build \
    --upload \
    --build-cache-path $PWD/build/build/cache \
    --build-path $PWD/build/build/compile \
    --warnings all
elif [ "$1" == "tracker" ];
then
    echo "Compiling tracker"
    find ./tracker -mindepth 1 -type f -exec cp -t ./build -i '{}' +
    mv ./build/tracker.ino ./build/build.ino
    ./arduino-cli compile \
    -p $2 \
    -b esp32:esp32:esp32 build \
    --upload \
    --build-cache-path $PWD/build/build/cache \
    --build-path $PWD/build/build/compile \
    --warnings all
else
    echo "Invalid target"
    echo "<box|tracker> <COM>"
fi

echo "Done!"
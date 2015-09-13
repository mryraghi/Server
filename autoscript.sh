#!/bin/bash

DIR="bin"
git pull

#checks if bin directory exists, if yes delete it
if [ -d "$DIR" ]; then
   rm -rf $DIR
fi

mkdir $DIR
cd $DIR
cmake ../
make
./tcp_echo 8080
#!/bin/sh

set -e

SHELL_FOLDER=$(cd "$(dirname "$0")";pwd)
cd $SHELL_FOLDER

if [ "$1" = "clean" ]; then
	rm -rf build
	exit 0
fi

rm -rf build
mkdir build
cd build
cmake ..
make -j24

cp test-person-detect ../test-person-detect-release

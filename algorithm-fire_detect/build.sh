#!/bin/sh

set -e

SHELL_FOLDER=$(cd "$(dirname "$0")";pwd)
cd $SHELL_FOLDER

if [ "$1" = "clear" ]; then
	rm -rf build
	exit 0
fi

rm -rf build
mkdir build
cd build
cmake ..
make -j24

cp test-fire-detect ../test-fire-detect-release

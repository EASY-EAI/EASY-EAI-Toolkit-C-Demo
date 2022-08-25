#!/bin/sh

set -e

SHELL_FOLDER=$(cd "$(dirname "$0")";pwd)
cd $SHELL_FOLDER

# clear
if [ "$1" = "clear" ]; then
	rm -rf build
	exit 0
fi

# build
rm -rf build
mkdir build
cd build
cmake ..
make -j24

# release
mv test-* ../Release

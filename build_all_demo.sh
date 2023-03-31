#/bin/bash

set -e

SHELL_FOLDER=$(cd "$(dirname "$0")";pwd)
cd $SHELL_FOLDER

release_path="Release"
algorithm_list=`ls -d algorithm-*`
common_list=`ls -d common-*`
media_list=`ls -d media-*`
netProtocol_list=`ls -d netProtocol-*`
peripheral_list=`ls -d peripheral-*`

alldemo="$algorithm_list $common_list $media_list $netProtocol_list $peripheral_list"

usage()
{
	echo "DESCRIPTION"
	echo "LMO toolkit-c-demo compile tool."
	echo " "
	echo "SYNOPSIS"
	echo "	./build_all_demo.sh [clear]"
}

clear_api()
{
	for var in ${alldemo[@]}
	do
		if [ -e $var/build.sh ]; then
			cd $var
			./build.sh clear
			cd - > /dev/null
		fi
	done
}

main() {
#	for var in ${alldemo[@]}
#	do
#		echo $var
#	done

	if [ $# -eq 1 ]; then
		if [ $1 == "clear" ]; then
			clear_api
		else
			usage
		fi

		exit 0
	fi
	
	### 编译所有demo
	for var in ${alldemo[@]}
	do
		if [ -e $var/build.sh ]; then
			cd $var
			./build.sh clear
			./build.sh
			cd - > /dev/null
		fi
	done
}

main "$@"


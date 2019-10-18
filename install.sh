#!/usr/bin/env bash

export PREFIX=/usr/local/

export USE_BUILTIN_PROTOBUF=0

while getopts "h?gp:" opt; do
    case "$opt" in
    h|\?)
        echo "install.sh [-h] [-g] [-p PREFIX]"
	echo "		-h		help"
	echo "		-g 		activate the build of the third party protobuf for sentencepiece (default is activated)"
	echo "		-p PREFIX	specify a prefix (default /usr/local/)"
        exit 0
        ;;
    g)  USE_BUILTIN_PROTOBUF=1
        ;;
    p)  PREFIX=$OPTARG
        ;;
    esac
done


#if [ -n "$1" ]
#then
#    export PREFIX=$1
#fi 


set -eou pipefail

echo "Prefix set to $PREFIX"
export CMAKE_PREFIX_PATH=$PREFIX

export CXXFLAGS="-I$PREFIX/include -L$PREFIX/lib"

set -eou pipefail

echo "Installing dependencies (fastText)"

pushd third_party/fastText
        rm -rf build
        mkdir -p build
        pushd build
                cmake .. -DCMAKE_INSTALL_PREFIX="${PREFIX}" -DCMAKE_BUILD_TYPE=Release
                make -j 8 && make install
        popd
popd

echo "Installing dependencies (sentencepiece)"

pushd third_party/sentencepiece
        rm -rf build
        mkdir -p build
        pushd build
         	if [ $USE_BUILTIN_PROTOBUF -eq 1 ]
		then
        	        cmake -DCMAKE_INSTALL_PREFIX="${PREFIX}" -DCMAKE_BUILD_TYPE=Release -DSPM_USE_BUILTIN_PROTOBUF=OFF  Protobuf_PROTOC_EXECUTABLE=/usr/local/bin/protoc ..
		else
			cmake -DCMAKE_INSTALL_PREFIX="${PREFIX}" -DCMAKE_BUILD_TYPE=Release ..
		fi
                make -j 8 && make install
        popd
popd

echo "Installing qnlp-toolkit"
mkdir -p $PREFIX
rm -rf build
mkdir -p build
pushd build
	cmake .. -DCMAKE_INSTALL_PREFIX="${PREFIX}" -DCMAKE_PREFIX_PATH="${PREFIX}" -DCMAKE_BUILD_TYPE=Release 
	make -j 8 && make install
popd

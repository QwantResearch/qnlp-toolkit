#!/usr/bin/env bash

export PREFIX=/usr/local/

if [ -n "$1" ]
then
    export PREFIX=$1
fi 

set -eou pipefail

echo "Prefix set to $PREFIX"
export CMAKE_PREFIX_PATH=$PREFIX

export CXXFLAGS="-I$PREFIX/include -L$PREFIX/lib"

set -eou pipefail

echo "Installing dependencies (fastText)"

pushd vendor/fastText
        rm -rf build
        mkdir -p build
        pushd build
                cmake .. -DCMAKE_INSTALL_PREFIX="${PREFIX}" -DCMAKE_BUILD_TYPE=Release
                make -j 8 && make install
        popd
popd

echo "Installing dependencies (sentencepiece)"

pushd vendor/sentencepiece
        rm -rf build
        mkdir -p build
        pushd build
         
                cmake -DCMAKE_INSTALL_PREFIX="${PREFIX}" -DCMAKE_BUILD_TYPE=Release -DSPM_USE_BUILTIN_PROTOBUF=OFF  Protobuf_PROTOC_EXECUTABLE=/usr/local/bin/protoc ..
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

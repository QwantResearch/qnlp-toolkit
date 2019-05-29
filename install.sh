#!/usr/bin/env bash

export PREFIX=/usr/local/

echo "Prefix set to $PREFIX"

export CMAKE_PREFIX_PATH=$PREFIX

git submodule update --init --recursive

echo "Installing dependencies"

pushd vendor/fastText
	rm -rf build
	mkdir -p build
	pushd build
		cmake .. -DCMAKE_INSTALL_PREFIX="${PREFIX}" -DCMAKE_BUILD_TYPE=Release
		make -j 4 && make install
	popd
popd

echo "Installing qnlp-toolkit"
mkdir -p $PREFIX
rm -rf build
mkdir -p build
pushd build
	cmake .. -DCMAKE_INSTALL_PREFIX="${PREFIX}" -DCMAKE_BUILD_TYPE=Release 
	make -j 4 && make install
popd

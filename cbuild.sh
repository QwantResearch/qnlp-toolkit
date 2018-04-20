#!/bin/bash

mkdir build -pv 
pushd build
	cmake .. -DCMAKE_INSTALL_PREFIX=$HOME/Tools/qnlp-toolkit
	make -j4 && make install
popd


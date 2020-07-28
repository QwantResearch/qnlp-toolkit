#!/usr/bin/env bash

export PREFIX=/usr/local/

export NOT_USE_BUILTIN_PROTOBUF=0

while getopts "h?gp:" opt; do
    case "$opt" in
    h|\?)
        echo "install.sh [-h] [-g] [-p PREFIX]"
	echo "		-h		help"
	echo "		-p PREFIX	specify a prefix (default /usr/local/)"
        exit 0
        ;;
    g)  NOT_USE_BUILTIN_PROTOBUF=1
        ;;
    p)  PREFIX=$OPTARG
        ;;
    esac
done

set -eou pipefail

echo "Prefix set to $PREFIX"
export CMAKE_PREFIX_PATH=$PREFIX

export CXXFLAGS="-I$PREFIX/include -L$PREFIX/lib"


echo "Installing qnlp-toolkit"
mkdir -p $PREFIX
rm -rf build
mkdir -p build
pushd build
	cmake .. -DCMAKE_INSTALL_PREFIX="${PREFIX}" -DCMAKE_PREFIX_PATH="${PREFIX}" -DCMAKE_BUILD_TYPE=Release 
	make -j 8 && make install
popd

#!/usr/bin/env bash

#THIS_DIR=$(cd $(dirname $0); pwd)
#if [[ "$THIS_DIR" == *" "* ]]; then
#    echo "$THIS_DIR: nlp-toolkit cannot install to a path containing whitespace.
#Please try a different path, one without any spaces."
#    exit 1
#fi

#PREFIX=${PREFIX:-"${THIS_DIR}/install"}
export PREFIX=/usr/

echo "Prefix set to $PREFIX"

export CMAKE_PREFIX_PATH=$PREFIX

git submodule update --init --recursive

echo "Installing dependencies"

pushd vendor/fastText
rm -rf build
mkdir -p build
pushd build
#cmake .. -DCMAKE_INSTALL_PREFIX="${PREFIX}" -DCMAKE_BUILD_TYPE=Release 2>&1 >>$PREFIX/install_dependencies.log || exit 1
cmake .. -DCMAKE_INSTALL_PREFIX="${PREFIX}" -DCMAKE_BUILD_TYPE=Release
#(make 2>&1 >>$PREFIX/install_dependencies.log  || exit 1) && (make install 2>&1 >>$PREFIX/install_dependencies.log || exit 1)
make -j 4 && make install
popd
popd

#ls -alrth $PREFIX/bin/fast*
#exit

echo "Installing qnlp-toolkit"
mkdir -p $PREFIX
rm -rf build
mkdir -p build
pushd build
#cmake .. -DCMAKE_INSTALL_PREFIX="${PREFIX}" -DCMAKE_BUILD_TYPE=Release 2>&1 >>$PREFIX/install.log || exit 1
cmake .. -DCMAKE_INSTALL_PREFIX="${PREFIX}" -DCMAKE_BUILD_TYPE=Release 
#(make 2>&1 >>$PREFIX/install.log  || exit 1) && (make install 2>&1 >>$PREFIX/install.log || exit 1)
make -j 4 && make install
popd

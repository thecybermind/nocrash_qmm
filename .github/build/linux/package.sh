#!/bin/sh
mkdir -p package
cd package
rm -f *
cp ../README.md ./
cp ../LICENSE ./
cp ../bin/release/x86/nocrash_qmm.so ./
cp ../bin/release/x86_64/nocrash_qmm_x86_64.so ./

cd ..

#! /bin/bash

rm -r -f jdksavdecc
mkdir jdksavdecc
cp -a include/* jdksavdecc/
cp -a src/* jdksavdecc/
zip -r jdksavdecc.zip jdksavdecc
rm -r -f jdksavdecc


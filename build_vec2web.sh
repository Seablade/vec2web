#!/bin/sh

echo "Building dxflib, qcadlib, vec2web.."

if [ -z $QTDIR ]
then
	echo "QTDIR not set. Aborting.."
	exit
fi

cd dxflib
./configure
make
cd ..

cd qcadlib
make
cd ..

cd vec2web
make
cd ..

#!/bin/sh

QTDIR=/usr/local/qt
PATH=$QTDIR/bin:/bin
MANPATH=$QTDIR/doc/man
LD_LIBRARY_PATH=$QTDIR/lib
DISPLAY=:0.0
HOME=/x3ng/qcad2/vec2web

export QTDIR PATH MANPATH LD_LIBRARY_PATH DISPLAY HOME

cd /x3ng/qcad2/vec2web
./vec2web $1 $2 -x $3 -y $4
rm -f debug_*.log

echo "OK, vec2web works (from Shell Script)."

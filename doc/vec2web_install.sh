#!/bin/sh
# vec2web installation from CVS for sf.net registered developers and 
# anonymous users

# Default installation directory:
INSTALLDIR="$HOME/vec2web"

# Registered SourceForge User and Member of the projects dxflib and qcad2
# or anonymous if you are not registered on SourceForge
USER="anonymous"

# Your platform spec for Qt:
QMAKESPEC=$QTDIR/mkspecs/linux-g++

# No need to change anything below this line:
QTVERSION="3.0"
CVS_RSH=ssh

echo -n "Installation Directory [$INSTALLDIR]: "
read inp
if [ ! -z $inp ]
then
	INSTALLDIR=$inp
fi

echo -n "SourceForge User [$USER]: "
read inp
if [ ! -z $inp ]
then
	USER=$inp
fi

# Create installation path:
if [ -d $INSTALLDIR ]
then
	echo "Installation Directory exists already"
else
	mkdir -p "$INSTALLDIR"
fi

# VEC2WEB_MING enable user to build vec2web with SWF (Shockwave Flash)
# file format support. 

VEC2WEB_MING="n"

echo
echo "vec2web can generate SWF (Shockwave Flash) movies using the ming library (http://ming.sourceforge.net)."
echo
echo -n "Do you want do enable SWF support [$VEC2WEB_MING]: "
read VEC2WEB_MING

if [ $VEC2WEB_MING = "y" ]
then
	echo "Start Instation with SWF (Shockwave Flash) support."
	echo "Instaling MING (http://ming.sourceforge.net) now..."
	cd $INSTALLDIR
	#wget http://telia.dl.sourceforge.net/sourceforge/ming/ming-0.2a.tgz
	#tar -zxvf ming-0.2a.tgz
	#cd ming-0.2a
	cvs -z9 -d:pserver:anonymous@cvs.ming.sourceforge.net:/cvsroot/ming co ming
	cd ming
	make dynamic
	make static
fi

echo "Installing QCad II to: $INSTALLDIR. sf.net user: $USER"

if [ -z $QTDIR ]
then
	echo "Environment variable QTDIR not set!"
	echo "Please install Qt $QTVERSION and set the QTDIR variable to the install dir."
	echo "You can get Qt from http://www.trolltech.com"
	exit 1
fi



if [ $USER = "anonymous" ]
then
	echo "Installation via pserver as anonymous.."
	USER=":pserver:$USER"
fi

# Parameters: module, cvs server (cvs.blah.sf.net), libname (blah.a)
function install {
	echo
	echo "Installing $1:"
	echo

	if [ -d $INSTALLDIR/$1/CVS ]
	then
		echo "$1 is already installed and will be updated"
		cm="upd -d"
	else
		cm="co"
	fi

	cd "$INSTALLDIR"
	#if [ $USER = ":pserver:anonymous" ]
	#then
	#	cvs -d $USER@cvs.$2.sourceforge.net:/cvsroot/$2 login
	#fi
	cvs -z3 -d$USER@cvs.$2.sourceforge.net:/cvsroot/$2 $cm $1

	LOG="$INSTALLDIR/$1.log"
	cd $1
	>$LOG
	./configure  1>>$LOG 2>&1
	make         1>>$LOG 2>&1
	
	if [ $3 != "NA" ]
	then
		make install 1>>$LOG 2>&1
		make testing 1>>$LOG 2>&1

		if [ ! -f $INSTALLDIR/$1/lib/$3.a ]
		then
			echo "## Error while compiling $1. Please consult the logfile: $LOG"
		fi
	fi
}

install dxflib dxflib libdxf
install qcadlib qcad2 libqcad
install qcadguiqt qcad2 libqcadguiqt
#install qcad qcad2 NA     # only if you want QCad II as well
install vec2web vec2web NA

echo
echo "vec2web should now be compiled and ready in $INSTALLDIR/vec2web"
echo

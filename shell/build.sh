#!/bin/bash 

usage() {
   echo "usage: $0 <major> <minor> <release>"    
}

if [ ! $# -eq 3 ]; then
   usage
   #exit 1
fi


#${BS2_HOME-'hahaha'}
echo 'bs2_home:-'${BS2_HOME:-hahaha}
echo 'bs2_home'${BS2_HOME}


#echo 'bs2_home:='${BS2_HOME:=hahaha}
#echo 'bs2_home'${BS2_HOME}
if [ -z ${BS2_HOME+x} ]; then
   echo "BS2_HOME is unset!"
   exit 1
fi

CWD=$(pwd)
SVN_ROOT=$BS2_HOME
<<EOF
MAJOR=$1
MINOR=$2
RELEASE=$3
EOF

MAJOR=1
MINOR=2
RELEASE=3

RELEASE_TMP="/tmp/build_bs2_${MAJOR}_${MINOR}_${RELEASE}"
MEDIA_FOLDERS="bin conf pkg pyinstall"

# get the revision
if [ -z ${REVISION+x} ]; then
   REVISION=`svn info $SVN_ROOT -r HEAD |grep "Last Changed Rev:" |awk '{print $4}'`
fi

rm -rf $RELEASE_TMP
mkdir -p $RELEASE_TMP

for f in $MEDIA_FOLDERS; do
   svn export $SVN_ROOT/$f $RELEASE_TMP/$f 
done

#remove unnecessary pkg
pushd $RELEASE_TMP
tar cvzf $CWD/BS2-${MAJOR}.${MINOR}.${RELEASE}.${REVISION}.tar.gz ./
popd

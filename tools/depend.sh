#!/bin/bash

# name=`echo "$depend" | awk -F'\.git' '{print $1}' | awk -F'\/' '{print $NF}'`

source "./util.sh"

buildDir=".dep/"

if [ -d "$buildDir" ]; then 
    rm -rf "$buildDir"
fi
mkdir "$buildDir"

depends=`ls depends/*.sh`

for depend in $depends; do
    source "$depend"
    download "$gitUrl" "$projectName" "$buildDir"
done
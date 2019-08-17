#!/bin/sh

root=`cd $(dirname $0); pwd -P`
build_dir="$root/.build"

cmd=$1
clear()
{
    if [ -d "$build_dir" ]; then
        rm -rf "$build_dir"
    fi
}

create()
{
    mkdir "$build_dir"
}

_cmake()
{
    cd "$build_dir"
    cmake ..
}

_make()
{
    cd "$build_dir"
    make -j5
}

_remake()
{
    cd "$build_dir"
    make clean
    make -j5
}

recreate()
{
    clear
    create
}

rebuild()
{
    recreate
    _cmake
    _remake
}

if [ "$cmd" == "clear" ]; then
    clear
elif [ "$cmd" == "build" ]; then
    rebuild
elif [ "$cmd" == "remake" ]; then
    _remake
else
    echo "cmd in clear or build"
fi
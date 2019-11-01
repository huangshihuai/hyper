#!/bin/bash

download() {
    gitUrl="$1"
    project="$2"
    toDownload="$3"
    git clone $gitUrl "$toDownload"."/"."$project"
}
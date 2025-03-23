#!/bin/bash

if [[ $# -ne 1 ]]; then
    echo "GIT_DIR is missing"
    echo "usage: ${0} GIT_DIR"
    exit 1
fi
GIT_DIR="${1}"
GIT_DIR=$(realpath $GIT_DIR)
cd $GIT_DIR
if [[ ! -d .git ]]; then
    echo "GIT_DIR must be set to repo root, .git is missing in $GIT_DIR"
    exit 1
fi

echo "Checking code formatting..."
. env/bin/activate && find src/ include/ -regex ".*\.\(hpp\|cpp\|c\|h\)$" -execdir clang-format --style=LLVM --dry-run --Werror {} + ;
FORMATTING_EC=$?
if [[ $FORMATTING_EC -ne 0 ]]; then
	exit 1
fi

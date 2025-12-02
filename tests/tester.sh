#!/bin/bash

for i in {1..1000}; do
    file="test${i}.in"
    if [ ! -f "$file" ]; then
        continue
    fi
    outfile="test${i}.out"
    solfile="test${i}.sol.out"
    ./projeto < "$file" > "$outfile"
    if [ ! -f "$solfile" ]; then
        echo "$solfile not found."
    elif diff -q "$outfile" "$solfile" > /dev/null 2>&1; then
        echo "$file passed."
    else
        echo "$file failed."
    fi
done

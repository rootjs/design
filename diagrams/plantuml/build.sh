#!/bin/bash
for file in *.puml; do
    echo "Building: $file"
    plantuml -eps "$file"
    epstopdf "${file%.*}.eps" --outfile="../../latex/resources/${file%.*}.pdf"
    rm "${file%.*}.eps"
done

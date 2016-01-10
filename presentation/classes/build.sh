#!/bin/bash
for file in *.puml; do
    echo "Building: $file"
    plantuml -tpng "$file" -o "../resources/"
done

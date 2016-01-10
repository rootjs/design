#!/bin/sh
for filename in ../latex/*.tex; do
sed 's/\\textbf{\s/\\textbf{/g' $filename > temp && mv temp $filename
done

#!/bin/sh

sed 's/\([a-zA-Z.]*\)\.tex/\1/g' $1 > temp && mv temp $1

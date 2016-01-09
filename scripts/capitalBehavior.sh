#!/bin/sh

sed 's/behavior/Behavior/g' $1 > temp && mv temp $1

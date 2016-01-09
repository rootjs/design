python2 stripPumlComments.py ../diagrams/plantuml/architecture.puml > temp
./plant2tex temp > includes
mv *.tex ../latex 
mv includes ../latex/latexinput.tex
rm temp


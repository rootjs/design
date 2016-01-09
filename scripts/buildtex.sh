#python2 stripPumlComments.py ../diagrams/plantuml/architecture.puml > temp
./plant2tex ../diagrams/plantuml/architecture.puml > includes
mv *.tex ../latex 
mv includes ../latex/latexinput.tex



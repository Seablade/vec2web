#!/bin/sh
# This converts all dxf files in directory demo to PNG, PS and WBMP

rm test/*.ps
rm test/*.png

for inputFile in `find ./test -name "*.dxf"`
do
	echo "Input: $inputFile"
	outputFile=${inputFile%.*}
	echo "Output: $outputFile"
	./vec2web $inputFile $outputFile.png -x 800 -y 600
	./vec2web $inputFile $outputFile.jpeg -x 800 -y 600
	./vec2web $inputFile $outputFile.ps
	./vec2web $inputFile $outputFile.wbmp
done

rm debug_*.log

#!/bin/sh
# This converts all dxf files in directory demo to PNG, PS and WBMP

rm demo/*.ps
rm demo/*.png

for inputFile in demo/*.dxf
do
	outputFile=${inputFile%%.*}
	echo $outputFile
	./vec2web $inputFile $outputFile.png -x 800 -y 600 -z 2
	./vec2web $inputFile $outputFile.ps
	./vec2web $inputFile $outputFile.wbmp
done

#!/bin/sh
# This converts all dxf files in directory demo to PNG, PS and WBMP

rm test/*.png
rm test/*.gif
rm test/*.jpeg
rm test/*.xbm
rm test/*.xpm
rm test/*.pnm
rm test/*.mng
rm test/*.bmp
rm test/*.ps
rm test/*.wbmp

for inputFile in `find ./test -name "*.dxf"`
do
	echo "Input: $inputFile"
	outputFile=${inputFile%.*}
	echo "Output: $outputFile"
	./vec2web $inputFile $outputFile.png -x 800 -y 600
	./vec2web $inputFile $outputFile.gif -x 800 -y 600
	./vec2web $inputFile $outputFile.jpeg -x 800 -y 600
	./vec2web $inputFile $outputFile.xbm -x 800 -y 600
	./vec2web $inputFile $outputFile.xpm -x 800 -y 600
	./vec2web $inputFile $outputFile.pnm -x 800 -y 600
	./vec2web $inputFile $outputFile.mng -x 800 -y 600
	./vec2web $inputFile $outputFile.bmp -x 800 -y 600
	#./vec2web $inputFile $outputFile.ps
	#./vec2web $inputFile $outputFile.wbmp
done

rm debug_*.log

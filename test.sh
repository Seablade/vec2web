#!/bin/sh
# This converts all dxf files in directory demo to PNG, PS and WBMP

rm -f test/*.swf
rm -f test/*.png
rm -f test/*.gif
rm -f test/*.jpeg
rm -f test/*.xbm
rm -f test/*.xpm
rm -f test/*.pnm
rm -f test/*.mng
rm -f test/*.bmp
rm -f test/*.ps
rm -f test/*.wbmp
rm -f test/*.dxml

for inputFile in `find ./test -name "*.dxf"`
do
	echo "Input: $inputFile"
	outputFile=${inputFile%.*}
	echo "Output: $outputFile"
	./vec2web $inputFile $outputFile.swf -x 800 -y 600
	./vec2web $inputFile $outputFile.png -x 800 -y 600
	#./vec2web $inputFile $outputFile.gif -x 800 -y 600
	./vec2web $inputFile $outputFile.jpeg -x 800 -y 600
	./vec2web $inputFile $outputFile.xbm -x 800 -y 600
	./vec2web $inputFile $outputFile.xpm -x 800 -y 600
	#./vec2web $inputFile $outputFile.pnm -x 800 -y 600
	#./vec2web $inputFile $outputFile.mng -x 800 -y 600
	./vec2web $inputFile $outputFile.bmp -x 800 -y 600
	#./vec2web $inputFile $outputFile.ps -x 800 -y 600
	#./vec2web $inputFile $outputFile.wbmp -x 800 -y 600
	./vec2web $inputFile $outputFile.dxml -x 800 -y 600
done

rm debug_*.log

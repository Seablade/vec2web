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
	echo "  Output: $outputFile.swf"
	./vec2web $inputFile $outputFile.swf -x 800 -y 600
	echo "  Output: $outputFile.png"
	./vec2web $inputFile $outputFile.png -x 800 -y 600
	#echo "  Output: $outputFile.gif"
	#./vec2web $inputFile $outputFile.gif -x 800 -y 600
	echo "  Output: $outputFile.jpeg"
	./vec2web $inputFile $outputFile.jpeg -x 800 -y 600
	echo "  Output: $outputFile.xbm"
	./vec2web $inputFile $outputFile.xbm -x 800 -y 600
	echo "  Output: $outputFile.xpm"
	./vec2web $inputFile $outputFile.xpm -x 800 -y 600
	echo "  Output: $outputFile.pbm"
	./vec2web $inputFile $outputFile.pbm -x 800 -y 600
	echo "  Output: $outputFile.pgm"
	./vec2web $inputFile $outputFile.pgm -x 800 -y 600
	echo "  Output: $outputFile.ppm"
	./vec2web $inputFile $outputFile.ppm -x 800 -y 600
	#echo "  Output: $outputFile.mng"
	#./vec2web $inputFile $outputFile.mng -x 800 -y 600
	echo "  Output: $outputFile.bmp"
	./vec2web $inputFile $outputFile.bmp -x 800 -y 600
	echo "  Output: $outputFile.ps"
	./vec2web $inputFile $outputFile.ps -o l -s A4
	echo "  Output: ${outputFile}_bw.ps"
	./vec2web $inputFile ${outputFile}_bw.ps -b -o l -s A4
	echo "  Output: $outputFile.dxml"
	./vec2web $inputFile $outputFile.dxml -x 800 -y 600
done

rm debug_*.log

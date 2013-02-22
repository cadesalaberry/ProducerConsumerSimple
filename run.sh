make > /dev/null
if [ -e ./factory ]
	then
	echo "Asynchronous:"
	./factory -async -produce 6969
	#./factory 6969
	echo ""
	echo "Synchronous:"
	./factory -produce 6969
fi
if [ -e ./*.o ]
	then make clean > /dev/null
fi

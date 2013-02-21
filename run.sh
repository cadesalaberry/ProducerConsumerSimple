
if [ -e ./*.o ]
	then make clean > /dev/null
fi
make > /dev/null
if [ -e ./factory ]
	then
	echo "synchronous"
	./factory 999
	echo "asynchronous"
	./factory -async 999
fi
if [ -e ./*.o ]
	then make clean > /dev/null
fi

if [ -e ./*.o ]
	then make clean > /dev/null
fi
make > /dev/null
if [ -e ./factory ]
	then
	echo "synchronous"
	./factory 10
	echo "asynchronous"
	./factory -async 13
fi
if [ -e ./*.o ]
	then make clean > /dev/null
fi
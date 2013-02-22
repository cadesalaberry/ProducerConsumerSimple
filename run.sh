
if [ -e ./*.o ]
	then make clean > /dev/null
fi
make > /dev/null
if [ -e ./factory ]
	then
	echo "Synchronous:"
	./factory 999999
	echo ""
	echo "asynchronous:"
	./factory -async 999999
fi
if [ -e ./*.o ]
	then make clean > /dev/null
fi

PROG=factory
RPRT=report.csv

if [ -e ./*.o ]
	then make clean > /dev/null
fi
make > /dev/null
if [ -e ./$PROG ]
	then
	
	echo -n "Logging data for Synchronous... "
	echo "product, asynchronous, synchronous" > $RPRT
	
	for i in {0..100000..1000}
	do
		TA=$(./$PROG -profile -produce $i)
		TS=$(./$PROG -async -profile -produce $i)
		echo $i, $TA, $TS >> $RPRT
	done
	echo DONE
fi
if [ -e ./*.o ]
	then make clean > /dev/null
fi

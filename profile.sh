PROG=factory
SYNC=report_sync.csv
ASYNC=report_async.csv

if [ -e ./*.o ]
	then make clean > /dev/null
fi
make > /dev/null
if [ -e ./$PROG ]
	then
	
	echo -n "Logging data for Synchronous... "
	echo "product, time" > $SYNC
	
	for i in {0..100000..1000}
	do
		TIME=$(./$PROG -profile -produce $i)
		echo $i, $TIME >> $SYNC
	done
	echo DONE
	
	
	echo -n "Logging data for Asynchronous... "
	echo "product, time" > $ASYNC
	
	for i in {0..100000..1000}
	do
		TIME=$(./$PROG -async -profile -produce $i)
		echo $i, $TIME >> $ASYNC
	done
	echo DONE
	
fi
if [ -e ./*.o ]
	then make clean > /dev/null
fi

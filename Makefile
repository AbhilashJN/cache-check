all:clean cache-level cache-line

cache-level: cache-level.c
	gcc cache-level.c -o cache-level

cache-line: cache-line.c
	gcc cache-line.c -o cache-line

clean:
	rm -rf cache-level cache-line
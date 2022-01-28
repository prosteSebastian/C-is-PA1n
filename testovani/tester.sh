#!/bin/bash

for f in {001..004}; do
	./a.out < tests/$f.in.txt > $f2.out.txt

	if ! diff "tests/$f.out.txt" "$f2.out.txt" >/tmp/tmp.txt ; then
		echo "Chyba v testu $f"
		cat "/tmp/tmp.txt"
		exit 0;
	fi

done

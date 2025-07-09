#!/bin/bash

if [ ! -d "dif_test" ]; then
	mkdir dif_test
fi

if [ -f "dif_test/old_test.txt" ]; then
	rm dif_test/old_test.txt
fi

if [ -f "dif_test/new_test.txt" ]; then
	mv "dif_test/new_test.txt" "dif_test/old_test.txt"
fi

source ~/.bashrc
bash /home/efittant/42_minishell_tester/tester.sh m > dif_test/new_test.txt

if [ -f "dif_test/old_test.txt" ]; then
	diff "dif_test/old_test.txt" "dif_test/new_test.txt" > "dif_test/diff.txt"
fi

cat dif_test/diff.txt

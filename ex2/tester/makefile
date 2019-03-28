prog: main.c
	gcc main.c

run:
	./a.out unix_input-utf-16.txt unix_to_unix.txt -unix -unix
	./a.out unix_input-utf-16.txt unix_to_mac.txt -unix -mac
	./a.out unix_input-utf-16.txt unix_to_win.txt -unix -win
	./a.out mac_input-utf-16.txt mac_to_unix.txt -mac -unix
	./a.out mac_input-utf-16.txt mac_to_mac.txt -mac -mac
	./a.out mac_input-utf-16.txt mac_to_win.txt -mac -win
	./a.out win_input-utf-16.txt win_to_unix.txt -win -unix
	./a.out win_input-utf-16.txt win_to_mac.txt -win -mac
	./a.out win_input-utf-16.txt win_to_win.txt -win -win
#end part 1 normal file
	./a.out unix_input-utf-16.txt unix_to_unix_swap.txt -unix -unix -swap
	./a.out unix_input-utf-16.txt unix_to_mac_swap.txt -unix -mac -swap
	./a.out unix_input-utf-16.txt unix_to_win_swap.txt -unix -win -swap
	./a.out mac_input-utf-16.txt mac_to_unix_swap.txt -mac -unix -swap
	./a.out mac_input-utf-16.txt mac_to_mac_swap.txt -mac -mac -swap
	./a.out mac_input-utf-16.txt mac_to_win_swap.txt -mac -win -swap
	./a.out win_input-utf-16.txt win_to_unix_swap.txt -win -unix -swap
	./a.out win_input-utf-16.txt win_to_mac_swap.txt -win -mac -swap
	./a.out win_input-utf-16.txt win_to_win_swap.txt -win -win -swap
#end part 2 normal file and swap
	./a.out unix_input-utf-16.txt unix_to_unix_keep.txt -unix -unix -keep
	./a.out unix_input-utf-16.txt unix_to_mac_keep.txt -unix -mac -keep
	./a.out unix_input-utf-16.txt unix_to_win_keep.txt -unix -win -keep
	./a.out mac_input-utf-16.txt mac_to_unix_keep.txt -mac -unix -keep
	./a.out mac_input-utf-16.txt mac_to_mac_keep.txt -mac -mac -keep
	./a.out mac_input-utf-16.txt mac_to_win_keep.txt -mac -win -keep
	./a.out win_input-utf-16.txt win_to_unix_keep.txt -win -unix -keep
	./a.out win_input-utf-16.txt win_to_mac_keep.txt -win -mac -keep
	./a.out win_input-utf-16.txt win_to_win_keep.txt -win -win -keep
#end part 3 normal file and keep
check:
	file unix_to_unix.txt > results_from_run.txt
	file unix_to_mac.txt >> results_from_run.txt
	file unix_to_win.txt >> results_from_run.txt
	file mac_to_unix.txt >> results_from_run.txt
	file mac_to_mac.txt >> results_from_run.txt
	file mac_to_win.txt >> results_from_run.txt
	file win_to_unix.txt >> results_from_run.txt
	file win_to_mac.txt >> results_from_run.txt
	file win_to_win.txt >> results_from_run.txt
	echo "________________________________" >> results_from_run.txt
	echo "end part 1" >> results_from_run.txt
	echo "________________________________" >> results_from_run.txt
#end part 1
	file unix_to_unix_swap.txt >> results_from_run.txt
	file unix_to_mac_swap.txt >> results_from_run.txt
	file unix_to_win_swap.txt >> results_from_run.txt
	file mac_to_unix_swap.txt >> results_from_run.txt
	file mac_to_mac_swap.txt >> results_from_run.txt
	file mac_to_win_swap.txt >> results_from_run.txt
	file win_to_unix_swap.txt >> results_from_run.txt
	file win_to_mac_swap.txt >> results_from_run.txt
	file win_to_win_swap.txt >> results_from_run.txt
	echo "________________________________" >> results_from_run.txt
	echo "end part 2" >> results_from_run.txt
	echo "________________________________" >> results_from_run.txt
#end part 2
	file unix_to_unix_keep.txt >> results_from_run.txt
	file unix_to_mac_keep.txt >> results_from_run.txt
	file unix_to_win_keep.txt >> results_from_run.txt
	file mac_to_unix_keep.txt >> results_from_run.txt
	file mac_to_mac_keep.txt >> results_from_run.txt
	file mac_to_win_keep.txt >> results_from_run.txt
	file win_to_unix_keep.txt >> results_from_run.txt
	file win_to_mac_keep.txt >> results_from_run.txt
	file win_to_win_keep.txt >> results_from_run.txt
	echo "________________________________" >> results_from_run.txt
	echo "end part 3" >> results_from_run.txt
	echo "________________________________" >> results_from_run.txt
#end part 3




testencoding:
	diff results.txt results_from_run.txt >> test.txt

all: run check testencoding


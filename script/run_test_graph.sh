#!/bin/bash

# Copyright (c) 2019-2020, Adrien BLASSIAU and Corentin JUVIGNY

# Permission to use, copy, modify, and/or distribute this software
# for any purpose with or without fee is hereby granted, provided
# that the above copyright notice and this permission notice appear
# in all copies.

# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
# WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
# AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
# CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
# CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

dicho() {
	down=2
	up=$2
	found=0
	val=16
	middle=0
	int=0
	status=0
	solution=-1

	# echo "middle : $middle, up : $up, down : $down, val : $val"
	echo $1
	while [[ "$found" -ne "1" && "$down" -le "$up" ]]; do

		let "middle=($up + $down)/2"
		# echo "middle : $middle, up : $up, down : $down, val : $val"

		./bin/convert "inst/source/$1.col" "inst/test/$1.cspi" $middle
		./bin/main -f "inst/test/$1.cspi" -fc 1 -hvar 1 -to 5 -v 0
		status=$?
		if [[ "$status" -ne "0" ]]; then
			# echo "NO SOLUTION FOR $middle"
			down=$((middle+1))
		else
			# echo "SOLUTION FOR $middle"
			solution=$middle
			up=$((middle-1))
		fi
	done

	if [[ "$solution" != "-1" ]]; then
		echo "WE FOUND $solution"
	else
		echo "WE DIDN'T FOUND THE VALUE"
	fi
}

dicho $1 $2
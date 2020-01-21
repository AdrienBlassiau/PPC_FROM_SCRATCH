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


for (( j = 1; j < 6; j++ ));do
	bin/main -f "inst/test/queen5_5.cspi" -hval $j -fc 1 -to 10 >> $1
	bin/main -f "inst/test/queen6_6.cspi" -hval $j -fc 1 -to 10 >> $1
	bin/main -f "inst/test/queen7_7.cspi" -hval $j -fc 1 -to 10 >> $1
	bin/main -f "inst/test/queen8_8.cspi" -hval $j -fc 1 -to 10 >> $1
	bin/main -f "inst/test/myciel3.cspi" -hval $j -fc 1 -to 10 >> $1
	bin/main -f "inst/test/myciel4.cspi" -hval $j -fc 1 -to 10 >> $1
	bin/main -f "inst/test/myciel5.cspi" -hval $j -fc 1 -to 10 >> $1
	bin/main -f "inst/test/myciel6.cspi" -hval $j -fc 1 -to 10 >> $1
	echo "" >> $1
done

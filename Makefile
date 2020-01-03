#----------------------------------------------------------------------
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
#----------------------------------------------------------------------


#----------------------------------------------------------------------
#           GLOBAL MAKEFILE, NOT TO BE MODIFIED
#----------------------------------------------------------------------


CC=gcc -Wall -Wextra -std=c11 -O2 -pthread -lm

all : main

test : main_test.o test_unit.o tools.o hash_int.o compare_int.o compare_string.o compare_tuple.o set.o avl.o domain.o variable.o tuple.o constraint.o stack.o instance.o duo.o Sstruct.o counter.o count.o
	cd obj/ && $(CC) $^ -o ../bin/$@ -lm -lcunit

main : main.o tools.o hash_int.o compare_int.o compare_string.o compare_tuple.o set.o avl.o domain.o variable.o tuple.o constraint.o stack.o instance.o read_file.o csp.o problem.o duo.o Sstruct.o counter.o count.o
	cd obj/ && $(CC) $^ -o ../bin/$@ -lm

main.o : src/main.c
	$(CC) -c $< -o obj/$@

domain.o : src/domain.c src/domain.h
	$(CC) -c $< -o obj/$@

variable.o : src/variable.c src/variable.h
	$(CC) -c $< -o obj/$@

tuple.o : src/tuple.c src/tuple.h
	$(CC) -c $< -o obj/$@

constraint.o : src/constraint.c src/constraint.h
	$(CC) -c $< -o obj/$@

tools.o : src/tools.c src/tools.h
	$(CC) -c $< -o obj/$@

avl.o : src/avl.c src/avl.h
	$(CC) -c $< -o obj/$@

stack.o : src/stack.c src/stack.h
	$(CC) -c $< -o obj/$@

set.o : src/set.c src/set.h
	$(CC) -c $< -o obj/$@

hash_int.o : src/hash_int.c src/hash_int.h
	$(CC) -c $< -o obj/$@

instance.o : src/instance.c src/instance.h
	$(CC) -c $< -o obj/$@

csp.o : src/csp.c src/csp.h
	$(CC) -c $< -o obj/$@

problem.o : src/problem.c src/problem.h
	$(CC) -c $< -o obj/$@

duo.o : src/duo.c src/duo.h
	$(CC) -c $< -o obj/$@

Sstruct.o : src/Sstruct.c src/Sstruct.h
	$(CC) -c $< -o obj/$@

counter.o : src/counter.c src/counter.h
	$(CC) -c $< -o obj/$@

count.o : src/count.c src/count.h
	$(CC) -c $< -o obj/$@

compare_int.o : src/compare_int.c src/compare_int.h
	$(CC) -c $< -o obj/$@

compare_string.o : src/compare_string.c src/compare_string.h
	$(CC) -c $< -o obj/$@

compare_tuple.o : src/compare_tuple.c src/compare_tuple.h
	$(CC) -c $< -o obj/$@

data.o : src/data.c src/data.h
	$(CC) -c $< -o obj/$@

read_file.o : src/read_file.c src/read_file.h
	$(CC) -c $< -o obj/$@

main_test.o : test/main_test.c
	$(CC) -c $< -o obj/$@

test_unit.o : test/test_unit.c src/include.h
	$(CC) -c $< -o obj/$@

doxygen : doc/Doxyfile
	cd doc && doxygen ../$<

.PHONY: clean
clean :
	rm -f obj/*
	rm -rf doc/html/*
	rm -rf doc/latex/*
	rm -rf bin/*

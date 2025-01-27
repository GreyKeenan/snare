default:

gccflags= \
	-std=c99 \
	-Wpedantic \
	-Wall \
	-Wextra \
	-iquote . \
	-iquote ..

test: ./a.out
	./a.out $(args)

list:
	gcc $(gccflags) \
		\
		$(args) \
		\
		tests/list.c \
		list.c \

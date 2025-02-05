default:

guroot= ../../subs/gu/src

gccflags= \
	-std=c99 \
	-Wpedantic \
	-Wall \
	-Wextra \
	-iquote . \
	-iquote .. \
	-iquote $(guroot)

lgu= \
	-L $(guroot) \
	-l gu

test: ./a.out
	./a.out $(args)

fortune: ../libdot.a
	gcc $(gccflags) \
		\
		$(args) \
		\
		tests/fortune.c \
		fortune.c \
		\
		-L .. \
		-l dot \
		$(lgu)

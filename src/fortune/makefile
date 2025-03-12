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

comp:
	gcc $(gccflags) \
		\
		$(args) \
		\
		voronoi.c \
		beach.c \
		breakpoint.c \
		\
		-lm \
		$(lgu)



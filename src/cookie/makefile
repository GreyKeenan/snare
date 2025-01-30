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

fortune:
	gcc $(gccflags) \
		$(args) \
		tests/fortune.c \
		fortune.c \
		\
		-L .. \
		-l gunc \
		-l chalk \

addedge:
	gcc $(gccflags) \
		$(args) \
		tests/addEdge.c \
		fortune.c \
		\
		-L .. \
		-l gunc \

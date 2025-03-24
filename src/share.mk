
ifndef root
$(error <root> is not set)
endif

guroot= $(root)/../subs/gu/src

gccflags= \
	-std=c99 \
	-Wpedantic \
	-Wall \
	-Wextra \
	-iquote .

obdir= objects

default:

guroot= ../subs/gu/src

gccflags= \
	-std=c99 \
	-Wpedantic \
	-Wall \
	-Wextra \
	-iquote . \
	-iquote $(guroot)

cfiles= \
	main.c

links= \
	-L . \
	-l dot \
	\
	-L $(guroot) \
	-l gu \

obdir= objects

# ==========

dev: \
	$(guroot)/libgu.a \
	libdot.a \
	\
	main.c
	
	gcc $(gccflags) \
		\
		$(args) \
		\
		$(cfiles) \
		\
		$(links)

run: a.out
	./a.out $(args)

clean:
	rm -rf */objects/*.o
	rm -f */a.out
	rm -f lib*.a
	rm -f a.out

# ==========

library: $(lib_requires)
	cd $(lib_name) \
	&& \
	gcc $(gccflags) \
		-c \
		-iquote .. \
		\
		$(lib_args) \
		\
		$(lib_cfiles) \
		\
		$(lib_links) \
	&& \
	mkdir -p $(obdir) \
	&& \
	mv *.o $(obdir)
	ar rcs lib$(lib_name).a $(lib_name)/$(obdir)/*.o

# ==========

all:
	make dot

.PHONY: dot
dot:
	make library lib_name=dot \
		lib_cfiles=" \
			random.c \
		" \
		lib_links=" \
			-lm \
		"

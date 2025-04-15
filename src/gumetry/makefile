default:

# ==========

root= ..
include $(root)/share.mk

gccflags += -iquote $(guroot)

# ==========

name= gumetry

cfiles= \
	cvpoly.c \
	line.c \
	triangle.c \

# ==========

lib:
	gcc -c $(gccflags) $(args) $(cfiles) $(links)
	mkdir -p $(obdir)
	mv *.o $(obdir)
	ar rcs $(root)/lib$(name).a $(obdir)/*.o

testcomp:
	gcc $(gccflags) -iquote tests $(args) \
		tests/$(tf) \
		\
		-L $(root) -l $(name) \
		-L $(guroot) -l gu \
		-lm \
		$(links)

# ==========

.PHONY: test
test: ./a.out
	./a.out $(args)

rpoints:
	make testcomp "tf=rpoints.c" "links=-lSDL2"

lineside:
	make testcomp "tf=lineside.c"

intersect:
	make testcomp "tf=intersect.c"

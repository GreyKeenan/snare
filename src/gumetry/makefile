default:

# ==========

root= ..
include $(root)/share.mk

gccflags += -iquote $(guroot)

# ==========

name= gumetry

cfiles= \
	cvpoly.c \

links= \
	-lm \
	-L $(guroot) -l gu \

# ==========

lib:
	gcc -c $(gccflags) $(args) $(cfiles) $(links)
	mkdir -p $(obdir)
	mv *.o $(obdir)
	ar rcs $(root)/lib$(name).a $(obdir)/*.o

# ==========

.PHONY: test
test: ./a.out
	./a.out $(args)


rpoints:
	gcc $(gccflags) $(args) \
		\
		test/rpoints.c \
		cvpoly.c \
		\
		-lm \
		-lSDL2 \
		-L $(guroot) -l gu

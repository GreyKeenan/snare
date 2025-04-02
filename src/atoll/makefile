default:

# ==========

root= ..
include $(root)/share.mk

gccflags += -iquote $(guroot)

# ==========

name= atoll

cfiles= \
	diagram.c \
	coast.c \

links= \
	-L $(guroot) -l gu \

# ==========

lib:
	gcc -c $(gccflags) $(args) $(cfiles)
	mkdir -p $(obdir)
	mv *.o $(obdir)
	ar rcs $(root)/lib$(name).a $(obdir)/*.o

# ==========

.PHONY: test
test: ./a.out
	./a.out $(args)


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

# ==========

lib:
	gcc -c $(gccflags) $(args) $(cfiles)
	mkdir -p $(obdir)
	mv *.o $(obdir)
	ar rcs $(root)/lib$(name).a $(obdir)/*.o

testcomp:
	gcc $(gccflags) $(args) \
		tests/$(tf) \
		\
		-L $(root) -l $(name) \
		-L $(guroot) -l gu \
		$(links)

# ==========

.PHONY: test
test: ./a.out
	./a.out $(args)

diagram_init:
	make testcomp "tf=diagram_init.c"



src= src
obdir= objects

gccflags= \
	-std=c99 \
	-Wpedantic \
	-Wall \
	-Wextra \
	-iquote .

default: \
	$(src)/libgunc.a\
	\
	$(src)/main.c
	
	cd $(src) && \
	gcc $(gccflags) \
		-o ../a.out \
		\
		$(args) \
		\
		main.c \
		\
		-L . \
		-l gunc

run: ./a.out
	./a.out $(args)

gunc: $(src)/gunc
	cd $(src)/gunc \
	&& \
	gcc $(gccflags) \
		-c \
		\
		$(args) \
		\
		file_logger.c \
		\
	&& \
	mkdir -p $(obdir) \
	&& \
	mv *.o $(obdir)
	ar rcs $(src)/libgunc.a $(src)/gunc/$(obdir)/*.o \

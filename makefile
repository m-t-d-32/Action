outobjdir = ./obj
outexedir = ./bin
outsrcdir = ./src

exe = $(outexedir)/main.exe

objects  = $(outobjdir)/*.o
			
cppfiles = $(outsrcdir)/*.cpp
			
cfiles   = $(outsrcdir)/*.c

srcfiles = $(outsrcdir)/*.*
			
$(exe):   	$(objects)
			g++ -o main.exe $(objects)
			mv main.exe $(outexedir)
			
$(objects): $(srcfiles)
			g++ -c $(cppfiles)
			gcc -c $(cfiles)
			mv *.o $(outobjdir)

clean: 
			rm -rf $(objects)
			rm -rf $(exe)
			rm -rf main.exe
			rm -rf *.o
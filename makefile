outobjdir = ./obj
outexedir = ./bin
outsrcdir = ./src
outtestdir = ./test

exe = $(outexedir)/main.exe

objects  = $(outobjdir)/*.o
			
cppfiles = $(outsrcdir)/*.cpp
			
cfiles   = $(outsrcdir)/*.c

srcfiles = $(outsrcdir)/*.*

testfile = $(outtestdir)/main.cpp
			
$(exe):   	$(objects) $(testfile)
			g++ $(objects) $(testfile) -o main.exe 
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
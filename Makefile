options = -Wall -pedantic -std=c++11
executable = tp3
debug_exec = tp3.debug
.PHONY : push clean 

default : $(executable)

$(executable) : main.o carte.o 
	g++ -o $@ $^ $(options)

debug :
	g++ -o carte.o -c carte.cpp $(options) -DDEBUG
	g++ -o main.o -c main.cpp $(options) -DDEBUG
	g++ -o $(debug_exec) main.o carte.o $(options) -DDEBUG
	./autotests.exp ./$(debug_exec)

main.o : main.cpp carte.h
	g++ -o $@ -c $< $(options)

carte.o : carte.cpp carte.h
	g++ -o $@ -c $< $(options)

push :
	@make clean
	git add .
	git commit -m 'automated commit'
	git push origin master

clean : 
	rm -fr $(executable) $(debug_exec) *.out *.o

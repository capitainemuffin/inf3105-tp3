options = -Wall -pedantic -std=c++11
executable = tp3

.PHONY : push clean 

default : $(executable)

$(executable) : main.o carte.o 
	g++ -o $(executable) carte.o $(options)


main.o : main.cpp carte.h
	g++ -o main.o -c main.o $(options)

carte.o : carte.cpp carte.h
	g++ -o carte.o -c carte.h $(options)

push :
	@make clean
	git add .
	git commit -m 'automated commit'
	git push origin master

clean : 
	rm -fr tests *.out *.o




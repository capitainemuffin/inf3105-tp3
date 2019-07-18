options = -Wall -pedantic -std=c++11
executable = tp3

.PHONY : push clean 

default : $(executable)

$(executable) : main.o carte.o 
	g++ -o $@ $^ $(options)

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
	rm -fr $(executable) tests *.out *.o




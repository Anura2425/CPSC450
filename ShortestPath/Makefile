all:
	g++ main.cpp shortestPath.cpp
	./a.out

test:
	g++ main.cpp shortestPath.cpp
	./a.out test1.txt testoutput1.txt
	./a.out test2.txt testoutput2.txt
	./a.out test3.txt testoutput3.txt
	diff answer1.txt testoutput1.txt
	diff answer2.txt testoutput2.txt
	diff answer3.txt testoutput3.txt

clean:
	rm a.out
	rm testoutput1.txt
	rm testoutput2.txt
	rm testoutput3.txt


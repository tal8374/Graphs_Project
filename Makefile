ProgramGraph: main.o AutoVertex.o Vertex.o Edge.o UndefinedVerticeException.o InvalidInputException.o OutOfMemoryException.o RegularEdge.o CityEdge.o automathEdge.o
	g++ main.o AutoVertex.o Vertex.o Edge.o UndefinedVerticeException.o InvalidInputException.o OutOfMemoryException.o RegularEdge.o CityEdge.o automathEdge.o -o ProgramGraph

main.o: main.cpp SearchMethod.h Exception.h Graph.h
	g++ -c main.cpp

AutoVertex.o: AutoVertex.cpp AutoVertex.h Vertex.h
	g++ -c AutoVertex.cpp

Vertex.o: Vertex.cpp Vertex.h
	g++ -c Vertex.cpp

Edge.o: Edge.cpp Edge.h Vertex.h AutoVertex.h Exception.h InvalidInputException.h OutOfMemoryException.h UndefinedVerticeException.h
	g++ -c Edge.cpp

UndefinedVerticeException.o: UndefinedVerticeException.cpp UndefinedVerticeException.h Exception.h Vertex.h
	g++ -c UndefinedVerticeException.cpp

InvalidInputException.o: InvalidInputException.cpp InvalidInputException.h Exception.h
	g++ -c InvalidInputException.cpp

OutOfMemoryException.o: OutOfMemoryException.cpp OutOfMemoryException.h Exception.h
	g++ -c OutOfMemoryException.cpp

RegularEdge.o: RegularEdge.cpp RegularEdge.h Edge.h
	g++ -c RegularEdge.cpp

CityEdge.o: CityEdge.cpp CityEdge.h Edge.h
	g++ -c CityEdge.cpp

automathEdge.o: automathEdge.cpp Edge.h automathEdge.h
	g++ -c automathEdge.cpp

clean: 
	rm -f *.o

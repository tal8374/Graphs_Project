
#include "SearchMethod.h"
#include "Graph.h"
#include "Exception.h"
#include <string.h>
	using namespace std;

int main(int argc, char* argv[])
{

	if (argc < 3)
	{
		cout << "graph file path needed" << endl;
		cout << "graph type needed (-r / -c / -a)" << endl;
		exit(1);
	}

	string path, graph_Type, search_method, start_vertex, end_vertex;
	int graph_size = -1, index = 1;
	path = argv[index++];
	graph_Type = argv[index++];
	try {
		if (graph_Type == "-r")
		{
			if (argc < 5)
			{
				cout << "search_method needed (-bfs/ -dfs/ -dijkstra)" << endl;
				cout << "start vertex for search needed" << endl;
				exit(1);
			}
			search_method = argv[index++];
			start_vertex = argv[index++];
			if (argc == 7 && strcmp(argv[index], "-m") == 0)
			{
				graph_size = atoi(argv[index + 1]);
			}
			if (argc == 8 && strcmp(argv[index + 1],"-m") == 0)
			{
				graph_size = atoi(argv[index + 2]);
			}
			Graph<Vertex, RegularEdge> graph(graph_size);			
			graph.BuildGraphFromFile(path);			
			if (search_method == "-bfs" || search_method == "-dijkstra")
			{
				if (argc < 6)
				{
					cout << "end vertex for search needed" << endl;
					exit(1);
				}
				end_vertex = argv[index++];
				if (search_method == "-bfs")
					SearchMethod<Graph<Vertex, RegularEdge> >::print(SearchMethod<Graph<Vertex, RegularEdge> >::BFS(graph, start_vertex, end_vertex));
				else
					SearchMethod<Graph<Vertex, RegularEdge> >::print(SearchMethod<Graph<Vertex, RegularEdge> >::Dijkstra(graph, start_vertex, end_vertex));
			}
			else if (search_method == "-dfs")
			{
				SearchMethod<Graph<Vertex, RegularEdge> >::print(SearchMethod<Graph<Vertex, RegularEdge> >::DFS(graph, start_vertex));
			}
			else
			{
				cout << "Invalid search method" << endl;
				exit(1);
			}

		}
	

	if (graph_Type == "-c")
	{
		if (argc < 5)
		{
			cout << "search_method needed (-bfs/ -dfs/ -dijkstra)" << endl;
			cout << "start vertex for search needed" << endl;
			exit(1);
		}
		search_method = argv[index++];
		start_vertex = argv[index++];
		if (argc == 7 && strcmp(argv[index], "-m") == 0)
		{
			graph_size = atoi(argv[index + 1]);
		}
		if (argc == 8 && strcmp(argv[index + 1], "-m") == 0)
		{
			graph_size = atoi(argv[index + 2]);
		}
		Graph<Vertex, CityEdge> graph(graph_size);		
		graph.BuildGraphFromFile(path);		
		if (search_method == "-bfs" || search_method == "-dijkstra")
		{
			if (argc < 6)
			{
				cout << "end vertex for search needed" << endl;
				exit(1);
			}
			end_vertex = argv[index++];
			if (search_method == "-bfs")
				SearchMethod<Graph<Vertex, CityEdge> >::print(SearchMethod<Graph<Vertex, CityEdge> >::BFS(graph, start_vertex, end_vertex));
			else
				SearchMethod<Graph<Vertex, CityEdge> >::print(SearchMethod<Graph<Vertex, CityEdge> >::Dijkstra(graph, start_vertex, end_vertex));
		}
		else if (search_method == "-dfs")
		{
			SearchMethod<Graph<Vertex, CityEdge> >::print(SearchMethod<Graph<Vertex, CityEdge> >::DFS(graph, start_vertex));
		}
		else
		{
			cout << "Invalid search method" << endl;
			exit(1);
		}


	}
	else if (graph_Type == "-a")
	{
		search_method = "automat";
		if(argc < 4)
		{
			cout<< "missing input file "<<endl;
			exit(1);
		}
		string input_file_path = argv[index++];
		if (argc == 6 && strcmp(argv[index], "-m") == 0)
		{			
			graph_size = atoi(argv[index+1]);
		}
		Graph<AutoVertex, AutomathEdge> Automat(graph_size);
		Automat.BuildGraphFromFile(path);
		fstream file;
		file.open(input_file_path.c_str());
		string line;
		if (!file) {
			cout << "File " << input_file_path << " Does Not Exist" << endl;
			exit(1);
		}
		while (getline(file, line))
		{
			if (line.length() > 0)
			{
				line.erase(line.find_last_not_of(" \n\r\t") + 1);
				SearchMethod<Graph<AutoVertex, AutomathEdge> >::check_Legal_Path(Automat, line);
			}
		}
	}
	}
	catch (Exception &e)
	{
		e.print_Error();
	}

	return 0;
}

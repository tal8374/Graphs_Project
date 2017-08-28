#ifndef _SEARCHMETHOD_
#define _SEARCHMETHOD_

#include <string>
#include <stack>
#include <vector>
#include "Graph.h"
#include <iostream>
#include <limits.h>

using namespace std;
template <class GraphType>
class SearchMethod
{
private:
	static stack<string> get_result_path_from_parent_child_map(GraphType &graph, map<string, string>& vertex_to_pre_vretex, const string& end);
public:
	SearchMethod();
	virtual ~SearchMethod();
	static stack<string> BFS(GraphType &graph, const string& start, const string& end);
	static stack<string> DFS(GraphType &graph, const string& start);
	static stack<string> Dijkstra(GraphType &graph, const string& start, const string& end);
	static void check_Legal_Path(GraphType &graph, string path);
	static void print(stack<string> vertex_path);
	static void do_Automath_Search(GraphType &graph, string file_path);
};

template <class GraphType>
SearchMethod<GraphType>::SearchMethod()
{
}

template <class GraphType>
SearchMethod<GraphType>::~SearchMethod()
{
}

template <class GraphType>
stack<string> SearchMethod<GraphType>::BFS(GraphType &graph, const string& start, const string& end)
{
	string result;
	queue<string> Q;
	map<string, string> vertex_to_pre_vretex;
	Q.push(start);
	vertex_to_pre_vretex[start] = "the_start";

	while (!Q.empty())
	{
		string temp = Q.front();
		Q.pop();
		if (temp == end)
		{
			result = temp;
			break;
		}
		if (graph.get_Vertexes().size() != 0)
		{
			vector<string> adj = graph.get_Vertexes().find(temp)->second->getOutEdges();
			for (vector<string>::const_iterator i = adj.begin(); i != adj.end(); ++i)
			{
				//Edge corrent_edge = graph.get_Edges().find(*i)->second;
				if (graph.get_Edges().size() != 0) {
					string next_vertex = graph.get_Edges().find(*i)->second->getToVertex().getName();
					if (vertex_to_pre_vretex.find(next_vertex) == vertex_to_pre_vretex.end())
					{
						vertex_to_pre_vretex[next_vertex] = temp;
						Q.push(next_vertex);
					}
				}
			}
		}
	}
	return get_result_path_from_parent_child_map(graph, vertex_to_pre_vretex, end);
}

template <class GraphType>
stack<string> SearchMethod<GraphType>::DFS(GraphType &graph, const string& start)
{
	stack<string> S, path, result;
	map<string, string> vertex_to_pre_vretex;
	if (graph.get_Vertexes().size() != 0)
		S.push(start);
	if(graph.get_Vertexes().find(start) == graph.get_Vertexes().end())
		throw InvalidInputException();
	string pre_vertex = "the_start";
	while (!S.empty())
	{
		string temp = S.top();
		if (vertex_to_pre_vretex.find(temp) == vertex_to_pre_vretex.end()) {
			vertex_to_pre_vretex[temp] = pre_vertex;
			
		}
		S.pop();
		pre_vertex = temp;
		if (graph.get_Vertexes().size() != 0) {
			Vertex t = *graph.get_Vertexes().find(temp)->second;
			vector<string> adj = graph.get_Vertexes().find(temp)->second->getOutEdges();
			bool go = false;
			for (vector<string>::const_iterator i = adj.begin(); i != adj.end(); ++i)
			{
				//Edge corrent_edge = graph.get_Edges().find(*i)->second;
				
				if (graph.get_Edges().size() != 0) {
					string next_vertex = graph.get_Edges().find(*i)->second->getToVertex().getName();					
					if (vertex_to_pre_vretex.find(next_vertex) == vertex_to_pre_vretex.end())
					{
						go = true;
						S.push(temp);
						S.push(next_vertex);
						break;
					}					
				}				
			}
			if (!go)
				path.push(temp);
		}
	}
	
	return path;
}


//this function is used to work with a map as a priority queue
pair<string, double> popMinFromMap(map<string, double>& vertex_map)
{
	double min = INT_MAX;
	pair<string, double> res("EMPTY", min);
	for (map<string, double>::iterator it = vertex_map.begin(); it != vertex_map.end(); it++)
	{
		if (it->second < min)
		{
			res = *it;
			min = it->second;
		}
	}
	vertex_map.erase(res.first);
	return res;
}

template <class GraphType>
stack<string> SearchMethod<GraphType>::Dijkstra(GraphType &graph, const string& start, const string& end)
{

	map<string, Vertex*> all_vertexs = graph.get_Vertexes();
	map<string, double> Q;
	for (map<string, Vertex*>::iterator it = all_vertexs.begin(); it != all_vertexs.end(); it++)
	{
		if (it->first == start)
			Q[it->first] = 0;
		else
			Q[it->first] = INT_MAX - 1;
	}

	map<string, string> vertex_to_pre_vretex;
	if (all_vertexs.find(start) == all_vertexs.end())
		throw InvalidInputException();
	string pre_vertex = "the_start";
	vertex_to_pre_vretex[start] = pre_vertex;
	while (!Q.empty())
	{
		pair<string, double>temp = popMinFromMap(Q);		
		pre_vertex = temp.first;
		if (graph.get_Vertexes().size() != 0) {
			Vertex  t = *all_vertexs.find(temp.first)->second;
			vector<string> adj = t.getOutEdges();
			for (vector<string>::const_iterator i = adj.begin(); i != adj.end(); ++i)
			{
				//Edge corrent_edge = graph.get_Edges().find(*i)->second;
				if (graph.get_Edges().size() != 0) {
					double edge_wieght = graph.get_Edges().find(*i)->second->getWieght();
					string next_vertex_name = graph.get_Edges().find(*i)->second->getToVertex().getName();
					if (Q.find(next_vertex_name) != Q.end()) {
						pair<string, double> next(next_vertex_name, Q[next_vertex_name]);
						if (next.second > temp.second + edge_wieght)
						{
							Q[next_vertex_name] = temp.second + edge_wieght;
							vertex_to_pre_vretex[next_vertex_name] = pre_vertex;
						}
					}
				}
			}
		}
	}
	return get_result_path_from_parent_child_map(graph, vertex_to_pre_vretex, end);
}

template <class GraphType>
stack<string> SearchMethod<GraphType>::get_result_path_from_parent_child_map(GraphType &graph, map<string, string>& vertex_to_pre_vretex, const string& end)
{
	stack<string> vertex_path;
	string result = end;
	if(graph.get_Vertexes().find(end) == graph.get_Vertexes().end())
		throw InvalidInputException();
	if (vertex_to_pre_vretex.find(end) == vertex_to_pre_vretex.end())
	{
		//cout << "There is no path";
		return vertex_path;
		//throw InvalidInputException();
	}
	vertex_path.push(result);
	//retrive all the vertexs along the path and put them in a stack
	while (vertex_to_pre_vretex[result] != "the_start")
	{
		string pre_vertex = vertex_to_pre_vretex[result];
		string edge_data = graph.get_Edges().find(pre_vertex + result)->second->get_Edge_Data();
		if (edge_data != "")
			vertex_path.push(edge_data);
		result = pre_vertex;
		vertex_path.push(result);
	}
	return vertex_path;
}

template <class GraphType>
void SearchMethod<GraphType>::print(stack<string> vertex_path)
{
	if (vertex_path.empty()) {
		cout << "There is no path" << endl;
		return;
	}
	while (!vertex_path.empty())
	{
		cout << vertex_path.top();
		if (vertex_path.size() != 1)
			cout << ",";
		vertex_path.pop();
	}
	cout << endl;
}

template <class GraphType>
void SearchMethod<GraphType>::check_Legal_Path(GraphType &graph, string path)
{
	if (path.length() == 0 && (graph.get_Vertexes().size() == 0 || graph.get_Edges().size() == 0))
	{
		cout << "FALSE" << endl;
		return;
	}
	string cur_Edge;
	AutoVertex cur_Vertex;
	for (map<string, Vertex*>::iterator it = graph.get_Vertexes().begin(); it != graph.get_Vertexes().end(); it++)
	{
		if (!dynamic_cast<AutoVertex*>(it->second))
			throw InvalidInputException();
		if (dynamic_cast<AutoVertex*>(it->second)->is_first())
		{
			cur_Vertex = *dynamic_cast<AutoVertex*>(it->second);
			break;
		}

	}
	while (path.length() > 0)
	{
		cur_Edge = path.substr(0, 1);
		path.erase(0, 1);

		vector<string> adj = cur_Vertex.getOutEdges();
		string next_vertex_name;
		for (vector<string>::const_iterator i = adj.begin(); i != adj.end(); ++i)
		{
			AutomathEdge* temp_edge = dynamic_cast<AutomathEdge*>(graph.get_Edges().find(*i)->second);
			if (temp_edge->get_edge_rule() == cur_Edge[0])
			{
				cur_Vertex = *dynamic_cast<AutoVertex*>(&temp_edge->getToVertex());
				cur_Edge = "";
				break;
			}
		}
	}
	if (cur_Vertex.get_Kind() != "$" || cur_Edge != "")
	{
		cout << "FALSE" << endl;
		return;
	}
	cout << "TRUE" << endl;
}


#endif

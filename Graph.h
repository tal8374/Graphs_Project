#ifndef _GRAPH_
#define _GRAPH_

#include <map>
#include <string>
#include <vector>
#include "Vertex.h"
#include "AutoVertex.h"
#include "RegularEdge.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include "CityEdge.h"
#include "automathEdge.h"
#include <fstream> 
#include <stdio.h>
using namespace std;

template <class VertexType, class EdgeType>
class Graph
{
protected:
	map<string, Vertex*> m_Vertexs;
	map<string, Edge*> m_Edges;
	int m_graph_Memory_Size;

public:
	Graph() : m_graph_Memory_Size(-1) {};
	Graph(int graph_Memory_Size);
	~Graph();
	void BuildGraphFromFile(const string file_path);
	map<string, vector<string> > getFileData(const string file_path);
	map<string, Vertex*>& get_Vertexes();
	map<string, Edge*>& get_Edges();
};

template <class VertexType, class EdgeType>
Graph<VertexType, EdgeType>::Graph(int graph_Memory_Size) : m_graph_Memory_Size(graph_Memory_Size)
{
}

template <class VertexType, class EdgeType>
Graph<VertexType, EdgeType>::~Graph()
{
	for (map<string, Vertex*>::iterator it = m_Vertexs.begin(); it != m_Vertexs.end(); it++)
	{
		delete it->second;
	}
	for (map<string, Edge*>::iterator it = m_Edges.begin(); it != m_Edges.end(); it++)
	{
		delete it->second;
	}
}
template <class VertexType, class EdgeType>
map<string, vector<string> > Graph<VertexType, EdgeType>::getFileData(const string file_path)
{

	string line, path = file_path , check = "";
	int count_keys = 0;
	fstream file;
	file.open(path.c_str());
	if (!file) {
		cout << "File " << file_path << " Does Not Exist" << endl;
		exit(1);
	}
	map<string, vector<string> > graph_metadata;
	while (getline(file, line))
	{
		if (line.length() > 1)
		{
			string key;
			string value;
			int index = 0;
			size_t pos = line.find(':');
			if (pos == 0 || pos == std::string::npos)
			{
				throw InvalidInputException();
			}
			key = line.substr(0, pos);
			if (key != check) {
				count_keys++;
				check = key;
			}
			value = line.substr(pos + 1);
			string::iterator end_pos = remove(key.begin(), key.end(), ' ');
			key.erase(end_pos, key.end());
			end_pos = remove(value.begin(), value.end(), ' ');
			value.erase(end_pos, value.end());
			value.erase(value.find_last_not_of(" \n\r\t") + 1);
			graph_metadata[key].push_back(value);

		}

	}
	file.close();
	if (graph_metadata.size() > 2 || count_keys > 2 )
		throw InvalidInputException();
	return graph_metadata;
}

template <class VertexType, class EdgeType>
void Graph<VertexType, EdgeType>::BuildGraphFromFile(const string file_path)
{
	int graph_Memory_Size = 0;
	map<string, vector<string> > graph_metadata = getFileData(file_path);
	if (graph_metadata.size() == 0)
		return;
	vector<string> vertexs, edges;
	string edge_type_data, vertex_type_data;
	EdgeType* test_Edge_type = new EdgeType();
	RegularEdge* re = dynamic_cast<RegularEdge*>(test_Edge_type);
	CityEdge* ce = dynamic_cast<CityEdge*>(test_Edge_type);
	AutomathEdge* ae = dynamic_cast<AutomathEdge*>(test_Edge_type);
	VertexType* test_Vertex_type = new VertexType();
	Vertex* normal_v = dynamic_cast<Vertex*> (test_Vertex_type);
	AutoVertex* auto_v = dynamic_cast<AutoVertex*>(test_Vertex_type);
	if (re && normal_v)
	{
		vertex_type_data = "V";
		edge_type_data = "E";
	}
	else if (ce && normal_v)
	{
		vertex_type_data = "C";
		edge_type_data = "R";
	}
	else if (ae && auto_v)
	{
		vertex_type_data = "S";
		edge_type_data = "T";
	}
	else
		throw InvalidInputException();
	delete test_Edge_type;
	delete test_Vertex_type;
	if (graph_metadata.find(vertex_type_data) != graph_metadata.end())
		vertexs = graph_metadata[vertex_type_data];
	else
	{
		throw InvalidInputException();
	}
	for (vector<string>::iterator it = vertexs.begin(); it != vertexs.end(); ++it)
	{
		VertexType* v = new VertexType(*it);
		if (vertex_type_data == "S" && m_Vertexs.size() == 0)
		{
			dynamic_cast<AutoVertex *>(v)->set_first();
		}
		if (m_Vertexs.find(v->getName()) != m_Vertexs.end())
			throw InvalidInputException();

		m_Vertexs[v->getName()] = v;
		graph_Memory_Size += v->get_Memory_Size();
	}
	if (graph_metadata.find(edge_type_data) != graph_metadata.end())
	{
		edges = graph_metadata[edge_type_data];
		for (vector<string>::iterator it = edges.begin(); it != edges.end(); ++it)
		{

			Edge* e = new EdgeType(*it, m_Vertexs);
			m_Edges[e->getName()] = e;
			graph_Memory_Size += e->get_Memory_Size();
		}
	}
	else if (graph_metadata.size() >= 2)
	{
		throw InvalidInputException();
	}
	graph_Memory_Size += 4 * m_Vertexs.size() + 2 * m_Edges.size();
	if (graph_Memory_Size > m_graph_Memory_Size && m_graph_Memory_Size != -1)
		throw OutOfMemoryException();

}

template <class VertexType, class EdgeType>
map<string, Vertex*>& Graph<VertexType, EdgeType>::get_Vertexes()
{
	return m_Vertexs;
}

template <class VertexType, class EdgeType>
map<string, Edge*>& Graph<VertexType, EdgeType>::get_Edges()
{
	return m_Edges;
}

#endif

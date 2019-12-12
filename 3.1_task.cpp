#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
#include <unordered_set>

struct IGraph {
    virtual ~IGraph() {}
    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;
    virtual int VerticesCount() const  = 0;
    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

class ArcGraph: public IGraph
{
public:
    ArcGraph(int n): vert_arr() {}
    ~ArcGraph(){}

    ArcGraph(const IGraph &graph) : vert_arr(graph.VerticesCount())
    {
        for (int i = 0; i < vert_arr.size(); i++)
        {
            std::vector <int> vert = graph.GetNextVertices(i);
            for (size_t j=0; j<vert.size();j++)
            {
                std::pair<int,int> par(i,vert[j]);
                vert_arr.push_back(par);
            }
        }
    }

    void AddEdge(int from, int to) override
    {
        assert(0 <= from);
        assert(0 <= to);
        std::pair<int ,int> par(from,to);
        vert_arr.emplace_back(from,to);

    }

    int VerticesCount() const override
    {
        std::unordered_set<int> vertic;
        size_t count=0;
        for (int i = 0; i < vert_arr.size() ; ++i) {
            if (vertic.find(vert_arr[i].first) == vertic.end())
            {
                vertic.insert(vert_arr[i].first);
                count++;
            }
            if (vertic.find(vert_arr[i].second) == vertic.end())
            {
                vertic.insert(vert_arr[i].second);
                count++;
            }

        }
        return count;
    }

    std::vector<int> GetNextVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < vert_arr.size());

        std::vector <int> next_vert;

        for (int i = 0; i < vert_arr.size() ; ++i) {
            if (vert_arr[i].first == vertex)
            {
                next_vert.push_back(vert_arr[i].second);
            }
        }
        return next_vert;
    }


    std::vector<int> GetPrevVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < vert_arr.size());
        std::vector<int> prev_vertices;

        for (int i = 0; i < vert_arr.size() ; ++i) {
            if (vert_arr[i].second == vertex)
            {
                prev_vertices.push_back(vert_arr[i].second);
            }
        }

        return prev_vertices;
    }

private:
    std::vector<std::pair<int ,int>> vert_arr;
};

class SetGraph: public IGraph
{
public:
    SetGraph(int n):vert_set(n){}
    ~SetGraph() {}

    SetGraph(const IGraph &graph) : vert_set(graph.VerticesCount())
    {
        for (int i = 0; i < vert_set.size(); i++)
        {
            std::vector <int> vert = graph.GetNextVertices(i);
            for (size_t j=0; j<vert.size();j++)
            {
                vert_set[i].insert(vert[j]);
            }
        }
    }

    void AddEdge(int from, int to) override
    {
        assert(0 <= from && from < vert_set.size());
        assert(0 <= to && to < vert_set.size());
        vert_set[from].insert(to);
    }

    int VerticesCount() const override
    {
        return (int)vert_set.size();
    }

    std::vector<int> GetNextVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < vert_set.size());
        std::vector <int> next_vert;
        for (auto i: vert_set[vertex])
        {
            next_vert.push_back(i);
        }
        return next_vert;
    }


    std::vector<int> GetPrevVertices(int vertex) const override
    {
        std::vector<int> prev_vertices;

        for (int from = 0; from < vert_set.size(); from++)
        {
            if (vert_set[from].find(vertex) != vert_set[from].end())
            {
                prev_vertices.push_back(from);
            }
        }
        return prev_vertices;
    }

private:
    std::vector<std::unordered_set<int>> vert_set;
};



class MatrixGraph: public IGraph
{
public:
    MatrixGraph(int n):matrix(n, std::vector<int>(n)){}
    ~MatrixGraph() {}

    MatrixGraph(const IGraph &graph) : matrix(graph.VerticesCount(),std::vector<int>(graph.VerticesCount()))
    {
        for (int i = 0; i < matrix.size(); i++)
        {
             std::vector <int> vert = graph.GetNextVertices(i);
             for (size_t j=0; j<vert.size();j++)
             {
                 matrix[i][vert[j]]=1;
             }
        }
    }

    void AddEdge(int from, int to) override
    {
        assert(0 <= from && from < matrix.size());
        assert(0 <= to && to < matrix.size());
        matrix[from][to]=1;
    }

    int VerticesCount() const override
    {
        return (int)matrix.size();
    }

    std::vector<int> GetNextVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < matrix.size());
        std::vector <int> next_vert;
        for (size_t i=0;i<matrix.size();i++)
        {
            if (matrix[vertex][i] == 1)
            {
                next_vert.push_back(i);
            }
        }
        return next_vert;
    }

    std::vector<int> GetPrevVertices(int vertex) const override
    {
        std::vector<int> prev_vertices;

        for (int from = 0; from < matrix.size(); from++)
        {
            if (matrix[from][vertex] == 1)
            {
                prev_vertices.push_back(from);
            }
        }
        return prev_vertices;
    }

private:
    std::vector<std::vector<int>> matrix;

};










class CListGraph: public IGraph
{
public:
    CListGraph(int n) : adjacency_lists(n) {}

    ~CListGraph() {}

    CListGraph(const IGraph &graph) : adjacency_lists(graph.VerticesCount())
    {
        for (int i = 0; i < adjacency_lists.size(); i++)
        {
            adjacency_lists[i] = graph.GetNextVertices(i);
        }
    }

    void AddEdge(int from, int to) override
    {
        assert(0 <= from && from < adjacency_lists.size());
        assert(0 <= to && to < adjacency_lists.size());
        adjacency_lists[from].push_back(to);
    }

    int VerticesCount() const override
    {
        return (int)adjacency_lists.size();
    }

    std::vector<int> GetNextVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < adjacency_lists.size());
        return adjacency_lists[vertex];
    }

    std::vector<int> GetPrevVertices(int vertex) const override
    {
        std::vector<int> prev_vertices;

        for (int from = 0; from < adjacency_lists.size(); from++)
        {
            for (int to: adjacency_lists[from])
            {
                if (to == vertex)
                {
                    prev_vertices.push_back(from);
                }
            }
        }
        return prev_vertices;
    }

private:
    std::vector<std::vector<int>> adjacency_lists;
};

void BFS(const IGraph &graph, int vertex, std::vector<bool> &visited, const std::function<void(int)> &func)
{
    std::queue<int> qu;
    qu.push(vertex);
    visited[vertex] = true;

    while (!qu.empty())
    {
        int current_vertex = qu.front();
        qu.pop();

        func(current_vertex);

        for (int next_vertex: graph.GetNextVertices(current_vertex))
        {
            if (!visited[next_vertex])
            {
                qu.push(next_vertex);
                visited[next_vertex] = true;
            }
        }
    }
}

void mainBFS(const IGraph &graph, const std::function<void(int)> &func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int vertex = 0; vertex < graph.VerticesCount(); vertex++)
    {
        if (!visited[vertex])
        {
            BFS(graph, vertex, visited, func);
        }
    }
}

void topological_sort_internal(const IGraph &graph, int vertex, std::vector<bool> &visited, std::deque<int> &sorted)
{
    visited[vertex] = true;
    for (int next_vertex: graph.GetNextVertices(vertex))
    {
        if (!visited[next_vertex])
        {
            topological_sort_internal(graph, next_vertex, visited, sorted);
        }
    }
    sorted.push_front(vertex);
}

std::deque<int> topological_sort(const IGraph &graph)
{
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::deque<int> sorted;

    for (int vertex = 0; vertex < graph.VerticesCount(); vertex++)
    {
        if (!visited[vertex])
        {
            topological_sort_internal(graph, vertex, visited, sorted);
        }
    }

    return sorted;
}

void print(const IGraph &graph)
{
    mainBFS(graph, [](int vertex) {std::cout << vertex << " ";});
    std::cout << std::endl;

    for (int i : topological_sort(graph))
        std::cout << i << " ";
    std::cout << std::endl;
}

int main(int argc, const char * argv[]) {
    ArcGraph graph(11);
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 5);
    graph.AddEdge(1, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(1, 5);
    graph.AddEdge(1, 6);
    graph.AddEdge(3, 2);
    graph.AddEdge(3, 4);
    graph.AddEdge(3, 6);
    graph.AddEdge(5, 4);
    graph.AddEdge(5, 6);
    graph.AddEdge(6, 4);

    graph.AddEdge(7, 8);
    graph.AddEdge(7, 9);

    graph.AddEdge(10, 0);

    std::cout << "graph:" << std::endl;
    print(graph);

    std::cout << "graph2:" << std::endl;
    SetGraph graph2(graph);
    print(graph2);

    return 0;
}

//0 1 5 2 3 6 4 7 8 9 10
//10 7 9 8 0 1 5 3 6 4 2
//0 5 1 6 4 3 2 7 9 8 10
//10 7 8 9 0 1 3 2 5 6 4
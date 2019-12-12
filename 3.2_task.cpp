#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
#include <unordered_set>
#include <map>

struct IGraph {
    virtual ~IGraph() {}
    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;
    virtual int VerticesCount() const  = 0;
    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
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
        vert_set[to].insert(from);
    }

    int VerticesCount() const override
    {
        return (int)vert_set.size();
    }

    std::vector<int> GetNextVertices(int vertex) const override
    {
        assert(0 <= vertex);
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

int MCW(const IGraph &graph,int from,int to)
{
    //first - min way ; second - count
    std::vector<std::pair<int,int>> states(graph.VerticesCount());
    std::queue<int> q;
    q.push(from);
    states[from].second = 1;
    while(!q.empty()){
        int v = q.front();
        q.pop();
        for(int i : graph.GetNextVertices(v)){
            if(states[i].second == 0){
                q.push(i);
                states[i].first = states[v].first + 1;
                states[i].second = states[v].second;
            }
            else if(states[i].first == states[v].first + 1)
            {
                states[i].second += states[v].second;
            }
        }
    }
    return states[to].second;
}


int main()
{
    size_t v=0,n=0;
    std::cin>>v>>n;
    SetGraph graph(v);
    int p1,p2;
    for (size_t i = 0; i < n ; ++i) {
        std::cin>>p1>>p2;
        graph.AddEdge(p1,p2);
    }
    std::cin>>p1>>p2;
    std::cout<<MCW(graph,p1,p2);
    return 0;
}
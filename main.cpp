#include <bits/stdc++.h>

using namespace std;

class travelling_salesman
{
public:
    int shortest_sum(int** edges_list,int** dp_arr,int visited,int mask,int position,int num_nodes)
    {
        if(mask == visited)
            return edges_list[position][0];

        if(dp_arr[mask][position] != -1)
            return dp_arr[mask][position];
        int ans = INT_MAX;
        for(int city=0; city<num_nodes; city++)
        {
            if((mask&(1<<city))==0)
            {
                int newAns = edges_list[position][city] + shortest_sum(edges_list,dp_arr,visited,mask|(1<<city), city,num_nodes);
                ans = min(ans, newAns);
            }
        }
        dp_arr[mask][position] = ans;
        return dp_arr[mask][position] = ans;
    }

    void path(vector<string> vertices_list,int** edges_list,int** dp_arr,int visited,int mask,int position,int num_nodes)
    {
        if(mask==visited) return;
        int ans = INT_MAX, chosenCity;

        for(int city=0; city<num_nodes; city++)
        {
            if((mask&(1<<city))==0)
            {
                int newAns = edges_list[position][city] + dp_arr[mask|(1<<city)][city];
                if(newAns < ans)
                {
                    ans = newAns;
                    chosenCity = city;
                }
            }

        }
        cout<<vertices_list[chosenCity]<<"  --->  ";
        path(vertices_list, edges_list,dp_arr,visited,mask|(1<<chosenCity),chosenCity,num_nodes);
    }
};
int main()
{
    int num_nodes,num_edges;
    cout<<"Enter number of Cities:- ";
    cin>>num_nodes;

    while(1)
    {
        cout<<"Enter number of paths :- ";
        cin>>num_edges;
        if(num_edges<=(num_nodes*(num_nodes-1))/2)
            break;
        else
            cout<<"Edges exceeded out of possible number";

    }

    int** edges_list = new int*[num_nodes];
    for(int i=0; i<num_nodes; i++)
    {
        edges_list[i] = new int[num_nodes];
        for(int j=0; j<num_nodes; j++)
            edges_list[i][j] = 0;
    }

    vector<string> vertices_list;
    for(int i=0; i<num_nodes; i++)
    {
        string temp;
        cout<<"Enter City Name :-";
        cin>>temp;
        vertices_list.push_back(temp);
    }

    cout<<endl<<endl;
    cout<<"Enter -1 if no path present between below cities"<<endl;
    for(int i=0; i<num_nodes; i++)
    {
        for(int j=0; j<i; j++)
        {
            if(i == j)
                continue;
            else
            {
                int weight;
                cout<<"Distance from "<<vertices_list[i]<<" to "<<vertices_list[j]<<": ";
                cin>>weight;
                edges_list[i][j] = weight;
                edges_list[j][i] = weight;
            }
        }
    }

    cout<<endl<<endl;
    int visited = (1<<num_nodes)-1;
    int m = 1<<num_nodes;
    int** dp_arr = new int*[m];
    for(int i=0; i<m; i++)
    {
        dp_arr[i] = new int[num_nodes];
        for(int j=0; j<num_nodes; j++)
            dp_arr[i][j] = -1;
    }
    for(int i=0; i<num_nodes; i++)
    {
        for(int j=0; j<num_nodes; j++)
            cout << edges_list[i][j] << " ";
        cout << endl;
    }
    cout << endl << endl;
    travelling_salesman travel;
    cout << "Minimum cost of path :- "<<travel.shortest_sum(edges_list,dp_arr,visited,1,0,num_nodes) << endl;
    cout<<vertices_list[0]<<"  --->  ";
    travel.path(vertices_list,edges_list,dp_arr,visited,1,0,num_nodes);
    cout<<vertices_list[0]<<endl<<endl;
    return 0;
}

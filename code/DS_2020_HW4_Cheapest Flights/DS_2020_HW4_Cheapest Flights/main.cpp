//
//  main.cpp
//  DS_2020_HW4_Cheapest Flights
//
//  Created by 顏浩昀 on 2020/12/9.
//

#include <iostream>
#include <string>

using namespace std;

int city;
int cost[101][101][11] = {0};
int maxcost;
bool vis[101];
int route(int, int, int, int);


int main(){
    string cmd;
    cin>>city;
    int from, to, ticket, airline;
    for(int i = 0; i < city; i++){
        vis[city] = false;
    }
    while (cin>>cmd) {
        if(cmd == "Add"){
            cin>>from>>to>>ticket>>airline;
            if(ticket < cost[from][to][airline] || cost[from][to][airline] == 0)
                cost[from][to][airline] = ticket;
        }else if(cmd == "Request"){
            cin>>from>>to>>maxcost;
            vis[from] = true;
            int ans = route(from, to, 0, -1);
            if(ans>maxcost){
                cout<<"-1\n";
            }else{
                cout<<ans<<"\n";
            }
            
            vis[from] = false;
        }else if(cmd == "Delete"){
            cin>>from>>to>>airline;
            cost[from][to][airline] = 0;
        }else{
            continue;
        }
    }
    return 0;
}

int route(int from, int to, int price, int line){
    //cout<<from<<" "<<to<<" "<<line<<" "<<price<<"\n";
    int minimum_cost = -1;
    int one_way_cost;
    if(from == to){
        maxcost = price;
        return price;
    }
    for(int i = 0; i < city; i++){
        if(!vis[i]){
            vis[i] = true;
            for(int j = 0; j < 11; j++){
                if(cost[from][i][j] != 0){
                    if(j != line && line != -1){
                        if(price+cost[from][i][j]+5 > maxcost){
                            continue;
                        }else{
                            one_way_cost = route(i, to, price+cost[from][i][j]+5, j);
                        }
                    }else{
                        if(price+cost[from][i][j] > maxcost){
                            continue;
                        }else{
                            one_way_cost = route(i, to, price+cost[from][i][j], j);
                        }
                    }
                    if(minimum_cost == -1){
                        if(one_way_cost!=-1){
                            minimum_cost = one_way_cost;
                        }
                    }else{
                        if(one_way_cost<minimum_cost && one_way_cost!=-1){
                            minimum_cost = one_way_cost;
                        }
                    }
                }
            }
            vis[i] = false;
        }
    }
    return minimum_cost;
}

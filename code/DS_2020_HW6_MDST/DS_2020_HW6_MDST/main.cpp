//
//  main.cpp
//  DS_2020_HW6_MDST
//
//  Created by 顏浩昀 on 2021/1/18.
//

#include <iostream>
#include <string>

int graph[101][101];
int dis[101][101];
int pi[101];
int r[101][101];
int dist[101];
double ecc_v;
double ecc_p;
bool connect = true;
int ver_i, edge_i, edge_j;
int total_path;

void length(int);
void AC(int);
void swap(int*, int*);
void shortest_v(int, int);
void shortest_e(int, int ,int);


void de(int v){
    std::cout<<"graph:\n";
    for(int i = 0; i < v; i++){
        for(int j = 0; j < v; j++){
            std::cout<<graph[i][j]<<" ";
        }
        std::cout<<"\n";
    }
    std::cout<<"dis:\n";
    for(int i = 0; i < v; i++){
        for(int j = 0; j < v; j++){
            std::cout<<dis[i][j]<<" ";
        }
        std::cout<<"\n";
    }
    std::cout<<"r:\n";
    for(int i = 0; i < v; i++){
        for(int j = 0; j < v; j++){
            std::cout<<r[i][j]<<" ";
        }
        std::cout<<"\n";
    }
}

int main() {
    int vertex;
    std::cin>>vertex;
    //initial
    for(int i = 0; i < vertex; i++){
        for(int j = 0; j < vertex; j++){
            if(i==j){
                graph[i][j] = 0;
                dis[i][j] = 0;
            }else{
                graph[i][j] = -1;
                dis[i][j] = -1;
            }
            r[i][j] = j;
        }
        dist[i] = 0;
        pi[i]=-1;
    }
    
    std::string cmd;
    while (std::cin>>cmd) {
        //initial
        ecc_p = ecc_v = 100000;
        connect = true;
        total_path = 0;
        if(cmd=="Add"){
            int v1, v2, weight;
            std::cin>>v1>>v2>>weight;
            graph[v1][v2] = weight;
            graph[v2][v1] = weight;
        }else if(cmd=="AC"){
            AC(vertex);
           // de(vertex);
            for(int a = 0; a < vertex; a++){
                for(int b = 0; b < vertex; b++){
                    if(dis[a][b] == -1){
                        connect = false;
                        break;
                    }
                }
            }
            if(connect){
                if(ecc_v <= ecc_p){
                    std::cout<<ver_i<<"\n";
                }else{
                    std::cout<<edge_i<<" "<<edge_j<<"\n";
                }
            }else{
                std::cout<<"Not connected graph\n";
            }
        }else if(cmd=="Diameter"){
            AC(vertex);
            for(int a = 0; a < vertex; a++){
                for(int b = 0; b < vertex; b++){
                    if(dis[a][b] == -1){
                        connect = false;
                        break;
                    }
                }
            }
            if(connect){
                if(ecc_v <= ecc_p){
                    std::cout<<2*ecc_v<<"\n";
                }else{
                    std::cout<<2*ecc_p<<"\n";
                }
            }else{
                std::cout<<"Not connected graph\n";
            }
        }else if(cmd=="Delete"){
            int v1, v2;
            std::cin>>v1>>v2;
            graph[v1][v2] = -1;
            graph[v2][v1] = -1;
        }else if(cmd=="SOSPD"){
            AC(vertex);
            if(connect){
                if(ecc_v<= ecc_p){
                    shortest_v(ver_i, vertex);
                    for(int a = 0;a < vertex; a++){
                        total_path+=dist[a];
                        std::cout<<dist[a]<<"\n";
                    }
                    std::cout<<total_path<<"\n";
                }else{
                    shortest_e(edge_i, edge_j, vertex);
                }
            }else{
                std::cout<<"Not connected graph\n";
            }
        }else{
            continue;
        }
    }
    return 0;
}


void length(int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            dis[i][j] = graph[i][j];
            //pi[i][j] = i;
        }
    }
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(dis[i][j] == -1){
                    if(dis[i][k] != -1 && dis[k][j] != -1){
                        dis[i][j] = dis[j][i] = dis[i][k]+dis[k][j];
                        
                        //std::cout<<i<<" "<<j<<" "<<k<<" "<<dis[i][j]<<"\n";
                    }
                }else{
                    if(dis[i][k] != -1 && dis[k][j] != -1 && (dis[i][k]+dis[k][j])<dis[i][j]){
                        dis[i][j] = dis[j][i] = dis[i][k]+dis[k][j];
                        
                        //std::cout<<i<<" "<<j<<" "<<k<<" "<<dis[i][j]<<"\n";
                    }
                }
            }
        }
    }
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void AC(int vertex){
    length(vertex);
    for(int k = 0; k < vertex; k++){
        for(int i = 0; i < vertex; i++){
            for(int j = 0; j < vertex-i-1; j++){
                if(dis[k][r[k][j]] < dis[k][r[k][j+1]]){
                    swap(&r[k][j], &r[k][j+1]);
                }
            }
        }
    }
    int a,b;
    for(int i = 0; i < vertex; i++){
        for(int j = 0; j < vertex; j++){
            for(a = 0, b = 1; b < vertex; b++){
                if(dis[j][r[i][b]] > dis[j][r[i][a]]){
                    if((ecc_p > (dis[i][r[i][b]] + dis[j][r[i][a]] + graph[i][j])/2) && graph[i][j] != -1){
                        ecc_p = (dis[i][r[i][b]] + dis[j][r[i][a]] + graph[i][j])/2;
                        edge_i = i; edge_j = j;
                    }
                    a = b;
                }
            }
        }
    }
    for(int k = 0; k < vertex; k++){
        if(dis[k][r[k][0]] < ecc_v){
            ecc_v = dis[k][r[k][0]];
            ver_i = k;
        }
    }
}


void shortest_v(int key, int n){
    bool vis[n];
    for(int i = 0; i < n;i++){
        vis[i] = false;
        dist[i] = graph[key][i];
        pi[i] = -1;
    }
    dist[key] = 0;
    vis[key] = true;
    int u;
    for(int i = 0; i < n-1; i++){
        int min = INT_MAX;
        for(int j = 0; j < n; j++){
            if(!vis[j] && dist[j] < min && dist[j] != -1){
                min = dist[j];
                u = j;
            }
        }
        vis[u] = true;
        for(int k = 0; k<n; k++){
            if(!vis[k] && dist[u]+graph[u][k] < dist[k] && graph[u][k] != -1){
                dist[k] = dist[u]+graph[u][k];
                pi[k] = u;
            }
        }
    }
}
void shortest_e(int e_i, int e_j, int n){
    int tmp_v;
    int a;
    for(tmp_v = 0;tmp_v < n; tmp_v++){
        if(tmp_v==e_j || tmp_v==e_j){
            continue;
        }else{
            a = (graph[e_i][e_j]+dis[e_j][tmp_v]-dis[e_i][tmp_v])/2;
            if(a<=0 || a>=graph[e_i][e_j]){
                
            }else{
                
            }
        }
    }
    
//    bool vis[n];
//    for(int i = 0; i < n;i++){
//        vis[i] = false;
//        dist[i] = graph[key][i];
//        pi[i] = -1;
//    }
//    dist[key] = 0;
//    vis[key] = true;
//    int u;
//    for(int i = 0; i < n-1; i++){
//        int min = INT_MAX;
//        for(int j = 0; j < n; j++){
//            if(!vis[j] && dist[j] < min && dist[j] != -1){
//                min = dist[j];
//                u = j;
//            }
//        }
//        vis[u] = true;
//        for(int k = 0; k<n; k++){
//            if(!vis[k] && dist[u]+graph[u][k] < dist[k] && graph[u][k] != -1){
//                dist[k] = dist[u]+graph[u][k];
//                pi[k] = u;
//            }
//        }
//    }
}

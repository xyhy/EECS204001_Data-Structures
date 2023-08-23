//
//  main.cpp
//  2020_DS_FinalProject
//
//  Created by 顏浩昀 on 2021/1/21.
//

#include <vector>
#include <csignal>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <map>
#include <queue>
#define VERT_NUM  82168

using namespace std;
int degree[VERT_NUM] = {0};
vector<int> clique;
vector<int> PA;
map<int, bool, less<int>> mapPA;
map<int, bool, less<int>> mapClique;

// TODO : kcore
vector<pair<int, int>> output;

vector<int> maximun_clique;
vector<vector<int>> graph(VERT_NUM);

void compute_clique(int vertex);
void addClique(int vertex);
void removePA(int vertex);
bool contain_in_clique(int vertex);
bool contain_in_PA(int vertex);


void compute_clique(int vertex)
{
    for(int i = 0; i < PA.size(); i++){
        while(PA.size()-i > 0){
            int node = PA.at(i);
            if(degree[node] < maximun_clique.size()){
                removePA(node);
            }else{
                addClique(node);
            }
        }
        if(clique.size() > maximun_clique.size()){
            maximun_clique = clique;
        }
        clique.clear();
        PA.clear();
        mapPA.clear();
        mapClique.clear();
        clique.push_back(vertex);
        mapClique.insert(map<int, bool, less<int> >::value_type(vertex, true));
        
    }
    return;
}

void addClique(int vertex){
    if(contain_in_clique(vertex)){
        return;
    }
    clique.push_back(vertex);
    mapClique.insert(map<int, bool, less<int> >::value_type(vertex, true));
    
    removePA(vertex);
    vector<int> eraselist;
    for(int i = 0; i < PA.size(); i++){
        int pavertex = PA.at(i);
        bool flag = true;
        for(int j = 0; j < graph[vertex].size(); j++){
            if(pavertex==graph[vertex][j]){
                flag = false;
                break;
            }
        }
        if(flag)    eraselist.push_back(pavertex);
    }
    for(int i=0; i<eraselist.size(); i++){
        removePA(eraselist.at(i));
    }
}


void removePA(int vertex){
    mapPA.erase(vertex);
    bool flag = false;
    std::vector<int>::iterator it;
    for(it = PA.begin(); it != PA.end(); it++){
        int ver = *it;
        if(ver == vertex){
            flag = true;
            break;
        }
    }
    if(flag)    PA.erase(it);
}

bool contain_in_clique(int vertex){
    map<int, bool, less<int>>::iterator it = mapClique.find(vertex);
    if(it == mapClique.end()){
        return false;
    }
    pair<int,bool> p = *it;
    if(p.second)    return true;
    return false;
}

bool contain_in_PA(int vertex){
    map<int, bool, less<int>>::iterator it = mapPA.find(vertex);
    if(it == mapPA.end()){
        return false;
    }
    pair<int, bool> p = *it;
    if(p.second)    return true;
    return false;
}


// TODO : kcore


int cmp_out(pair<int, int> a, pair<int, int> b){
    return a.first<b.first;
}

void signalHandler( int signum ) {
    /*
    In the signal handler, we output the current best clique that we found.
    */
    fstream out;
    out.open("clique.txt" , ios::out);
    sort(maximun_clique.begin() , maximun_clique.end());

    for(int v : maximun_clique){
        out<<v<<endl;
    }
    
    fstream out_k;
    out_k.open("kcore.txt", ios::out);
    
    sort(output.begin(), output.end(), cmp_out);
    for(auto v : output){
        out_k<<v.first<<" "<<v.second<<endl;
    }

    exit(signum);
}


int main(int argc , char *argv[])
{
    
    signal(SIGINT, signalHandler);
    freopen(argv[1] , "r" , stdin);
    int K = stoi(argv[2]); // K is the number of kcore.
    
    int max_degree = 0;
    
    // input data
    int A , B;
    while(cin >> A >> B){
        if(A == B){
            continue;
        }
        graph[A].push_back(B);
        graph[B].push_back(A);
        degree[A]++;
        if(degree[A] > max_degree)  max_degree = degree[A];
        degree[B]++;
        if(degree[B] > max_degree)  max_degree = degree[B];
    }
    for(int i = 0 ; i < VERT_NUM ; i++){
        sort(graph[i].begin(), graph[i].end());
    }
    
    
    // TODO : Kcore
    int List[VERT_NUM];
    queue<int> delList;
    bool vis[VERT_NUM];
    
    int kcore;
    bool flag = true;
    for(int i = 0; i < VERT_NUM; i++){
        if(degree[i] != 0){
            List[i] = 1;
        }
        vis[i] = false;
    }
    for(kcore = 1; kcore <= max_degree; kcore++){
        for(int i=0; i < VERT_NUM; i++){
            if(degree[i] >= kcore){
                flag = false;
                List[i] = kcore;
                if(degree[i] == kcore && !vis[i]){
                    delList.push(i);
                    vis[i] = true;
                }
            }
        }
        while (!flag) {
            while (!delList.empty()) {
                int del = delList.front();
                delList.pop();
                for(int a = 0; a < graph[del].size(); a++){
                    if(!vis[graph[del].at(a)]){
                        degree[graph[del].at(a)]--;
                        if(degree[graph[del].at(a)] == kcore){
                            delList.push(graph[del].at(a));
                            vis[graph[del].at(a)] = true;
                        }
                    }
                }
            }
            break;
        }
        if(flag)    break;
        flag = true;
    }

    
    fstream out_k;
    out_k.open("kcore.txt", ios::out);
    
    //sort(output.begin(), output.end(), cmp_out);
    for(int i = 0; i < VERT_NUM; i++){
        if(List[i] >= K){
            out_k<<i<<" "<<List[i]<<"\n";
        }
    }
    
    int maxkcorevertex;
    for(int i = 0; i < VERT_NUM; i++){
        if(List[i] == kcore-1){
            maxkcorevertex = i;
            break;
        }
    }
    
    clique.push_back(maxkcorevertex);
    mapClique.insert(map<int, bool, less<int> >::value_type(maxkcorevertex, true));
    for(int j = 0; j < graph[maxkcorevertex].size(); j++){
        PA.push_back(graph[maxkcorevertex][j]);
        mapPA.insert(map<int, bool, less<int>>::value_type(graph[maxkcorevertex][j], true));
    }
    compute_clique(maxkcorevertex);
    
    // TODO : clique
    for(int vertex = 0; vertex < VERT_NUM; vertex++){
        if(graph[vertex].empty()){
            continue;
        }else if(degree[vertex] < maximun_clique.size()){
            continue;
        }else{
            clique.clear();
            PA.clear();
            mapPA.clear();
            mapClique.clear();

            clique.push_back(vertex);
            mapClique.insert(map<int, bool, less<int> >::value_type(vertex, true));
            for(int j = 0; j < graph[vertex].size(); j++){
                PA.push_back(graph[vertex][j]);
                mapPA.insert(map<int, bool, less<int>>::value_type(graph[vertex][j], true));
            }
            compute_clique(vertex);
        }
    }

    
    
    /*
    Don't forget to write normal output here, in case your program terminated before SIGINT is received
//    */
//
    fstream out;
    out.open("clique.txt" , ios::out);
    sort(maximun_clique.begin() , maximun_clique.end());
    /*
    test1
    */
    for(int v : maximun_clique){
        out<<v<<endl;
    }
//
    

}

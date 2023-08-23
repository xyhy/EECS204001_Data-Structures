//
//  main.cpp
//  DS_2020_HW1_LinkedList
//
//  Created by 顏浩昀 on 2020/10/12.
//

#include <iostream>
#include <string>


class node{
    friend class chain;
public:
    node(int value=0):data(value), next(nullptr){};
    
private:
    int data;
    node *next;
};

class chain{
public:
    chain():first(nullptr),last(nullptr){};
    void InsertFront(int);
    void InsertBack(int);
    void InsertBefore(int,int);
    void InsertAfter(int,int);
    void Deletek(int);
    void DeleteFront();
    void DeleteBack();
    void Print();
    void Clear();
    void Reverse(int,int);
    node* find(int);
    node* find_pre(int);
private:
    node *first;
    node *last;
};


int main() {
    chain L;
    std::string op;
    int num1, num2;
    while (std::cin>>op) {
        if("InsertFront" == op){
            std::cin>>num1;
            L.InsertFront(num1);
        }else if("InsertBack" == op){
            std::cin>>num1;
            L.InsertBack(num1);
        }else if("InsertBefore" == op){
            std::cin>>num1>>num2;
            L.InsertBefore(num1, num2);
        }else if("InsertAfter" == op){
            std::cin>>num1>>num2;
            L.InsertAfter(num1, num2);
        }else if("Delete" == op){
            std::cin>>num1;
            L.Deletek(num1);
        }else if("DeleteFront" == op){
            L.DeleteFront();
        }else if("DeleteBack" == op){
            L.DeleteBack();
        }else if("Reverse" == op){
            std::cin>>num1>>num2;
            L.Reverse(num1, num2);
        }else if("Clear" == op){
            L.Clear();
        }else if("Print" == op){
            L.Print();
        }
    }
    return 0;
}

node* chain::find(int target){
    if(first == nullptr)    return nullptr;
    node *tmp = first;
    while (tmp != nullptr) {
        if(tmp->data == target) return tmp;
        else    tmp = tmp->next;
    }
    return nullptr;
}

node* chain::find_pre(int target){
    if(first == nullptr)    return nullptr;
    node *tmp = first;
    while (tmp->next != nullptr) {
        if(tmp->next->data == target) return tmp;
        else    tmp = tmp->next;
    }
    return nullptr;
}

void chain::InsertFront(int data){
    node *newone = new node(data);
    if(first == nullptr)    first = last = newone;
    else{
        newone->next = first;
        first = newone;
    }
}

void chain::InsertBack(int data){
    node *newone = new node(data);
    if(last == nullptr)     first = last = newone;
    else{
        last->next = newone;
        last = newone;
    }
}

void chain::InsertAfter(int target, int data){
    node *f = find(target);
    if(f == nullptr)    return;
    else if(f == last)    InsertBack(data);
    else{
        node *newone = new node(data);
        newone->next = f->next;
        f->next = newone;
    }
}

void chain::InsertBefore(int target, int data){
    node *f = find(target);
    node *f_pre = find_pre(target);
    if(f == nullptr)    return;
    else if(f == first)     InsertFront(data);
    else{
        node *newone = new node(data);
        f_pre->next = newone;
        newone->next = f;
    }
}

void chain::DeleteFront(){
    if (first == nullptr)   return;
    else if(first == last){
        node *tmp = first;
        first = last = nullptr;
        delete tmp;
    }
    else{
        node *del = first;
        first = del->next;
        delete del;
    }
}

void chain::DeleteBack(){
    if (first == nullptr) return;
    else if(first == last){
        node *tmp = first;
        first = last = nullptr;
        delete tmp;
    }
    else{
        node *del = last;
        node *tmp = first;
        while (tmp->next != last)   tmp = tmp->next;
        last = tmp;
        tmp->next = nullptr;
        delete del;
    }
}

void chain::Deletek(int target){
    node *f_pre = find_pre(target);
    node *f = find(target);
    if(f == nullptr)    return;
    else{
        if(f == first)      DeleteFront();
        else if(f == last)      DeleteBack();
        else{
            f_pre->next = f->next;
            delete f;
        }
    }
}

void chain::Reverse(int a, int b){ //a is near first.
    node *fa = find(a);
    node *fa_pre = find_pre(a);
    node *fb = find(b);
    if(first == nullptr)    return;
    else if(fa == nullptr || fb == nullptr)  return;
    else{
        node *tmp = fa->next;
        node *tmp_head = fa;
        node *tmp_next = tmp->next;
        tmp_head->next = fb->next;
        while (tmp != fb) {
            tmp->next = tmp_head;
            tmp_head = tmp;
            tmp = tmp_next;
            tmp_next = tmp_next->next;
        }
        tmp->next = tmp_head;
        tmp_head = tmp;
        if(fb == last)  last = fa;
        if(fa != first){
            fa_pre->next = tmp_head;
        }else{
            first = tmp_head;
        }
    }
}

void chain::Clear(){
    if(first == nullptr)    return;
    node *tmp;
    while(first != last){
        tmp = first;
        first = first->next;
        delete tmp;
    }
    tmp = first;
    first = last = nullptr;
    delete tmp;
}

void chain::Print(){
    if(first == nullptr)    std::cout<<"\n";
    else{
        node *out = first;
        while(out != nullptr){
            std::cout<<out->data<<" ";
            out = out->next;
        }
        std::cout<<"\n";
    }
}

//
//  main.cpp
//  DS_2020_HW2_Elementary arithmetic
//
//  Created by 顏浩昀 on 2020/10/28.
//

#include <iostream>
#include <string>
#include <cstdlib>


class node{
    friend class Stack;
public:
    node(char c):data(c), prev(nullptr), next(nullptr){};
private:
    char data;
    node *prev, *next;
};

class Stack{
public:
    Stack():front(nullptr),back(nullptr){};
    void pushfront(char);
    void popfront();
    void pushback(char);
    void popback();
    void print();
    void infix_to_postfix();
    void clear();
    int calculate();
    //bool valid();
private:
    node *front, *back;
};

Stack infix, postfix, op;
int op_count, num_count;
bool valid;
int flag = 0;
int num_op = 1; // 0 <= num, 1 <= op;

int main() {
    std::string input, cmd;
    char en;
    int de;
    std::cin>>input;
    for(int i = 0; i < input.size(); i++){
        if((input[i]>='0'&&input[i]<='9') || input[i]=='+' || input[i]=='-' || input[i]=='*' || input[i]=='/' || input[i]=='(' || input[i] == ')'){
            infix.pushback(input[i]);
        }else{
            continue;
        }
    }
    while (std::cin>>cmd) {
        if(cmd == "Enqueue"){
            std::cin>>en;
            infix.pushback(en);
        }else if(cmd == "Dequeue"){
            std::cin>>de;
            while(de--){
                infix.popfront();
            }
        }else if(cmd == "Print"){
            postfix.clear();
            op.clear();
            op_count = 0;
            num_count = 0;
            num_op = 1;
            valid = true;
            infix.infix_to_postfix();
            if(flag == 0){
                if(valid){
                    infix.print();
                    std::cout<<"\n";
                    postfix.print();
                    std::cout<<"\n";
                    int ans = postfix.calculate();
                    std::cout<<ans;
                }else{
                    infix.print();
                    std::cout<<"\n";
                    std::cout<<"Invalid";
                }
                flag = 1;
            }else{
                if(valid){
                    std::cout<<"\n";
                    infix.print();
                    std::cout<<"\n";
                    postfix.print();
                    int ans = postfix.calculate();
                    std::cout<<"\n";
                    std::cout<<ans;
                }else{
                    std::cout<<"\n";
                    infix.print();
                    std::cout<<"\n";
                    std::cout<<"Invalid";
                }
            }
            
        }
    }
}

void Stack::pushfront(char c){
    node *newone = new node(c);
    if(front == nullptr)    front = back = newone;
    else{
        newone->next = front;
        front->prev = newone;
        front = newone;
    }
}

void Stack::pushback(char c){
    node *newone = new node(c);
    if(back == nullptr)    front = back = newone;
    else{
        newone->prev = back;
        back->next = newone;
        back = newone;
    }
}

void Stack::popfront(){
    if(front == nullptr)    return;
    else{
        node *del = front;
        if(front == back){
            front = back = nullptr;
            delete del;
        }else{
            front = front->next;
            delete del;
        }
    }
}


void Stack::popback(){
    if(back == nullptr) return;
    else{
        node *del = back;
        if(front == back){
            front = back = nullptr;
            delete del;
        }else{
            back = back->prev;
            delete del;
        }
    }
}


void Stack::infix_to_postfix(){
    node *turn = this->front;
    while(turn != nullptr){
        if(turn->data>='0' && turn->data<='9'){
            if(num_op == 1){
                postfix.pushback(turn->data);
                num_count++;
                num_op = 0;
            }else{
                valid = false;
                break;
            }
        }else if(turn->data == '('){
            if(num_op == 1){
                op.pushback(turn->data);
            }else{
                valid = false;
                break;
            }
        }else if(turn->data == '*' || turn->data == '/'){
            if(num_op == 0){
                if (op.back != nullptr) {
                    if (op.back->data == '*' || op.back->data == '/'){
                        postfix.pushback(op.back->data);
                        op.popback();
                    }
                }
                op.pushback(turn->data);
                op_count++;
                num_op = 1;
            }else{
                valid = false;
                break;
            }
        }else if(turn->data == '+' || turn->data == '-'){
            if(num_op == 0){
                while(op.back != nullptr){
                    if(op.back->data == '*' || op.back->data == '/'){
                        postfix.pushback(op.back->data);
                        op.popback();
                    }else if(op.back->data == '+' || op.back->data == '-'){
                        postfix.pushback(op.back->data);
                        op.popback();
                        break;
                    }
                    else{
                        break;
                    }
                }
                op.pushback(turn->data);
                op_count++;
                num_op = 1;
            }else{
                valid = false;
                break;
            }
        }else if(turn->data == ')'){
            while (op.back != nullptr) {
                if(op.back->data == '('){
                    break;
                }else{
                    postfix.pushback(op.back->data);
                    op.popback();
                }
            }
            if(op.back == nullptr){
                valid = false;
            }else if(op.back->data == '('){
                op.popback();
            }
        }else{
            continue;
        }
        turn = turn->next;
    }

    while(op.back != nullptr){
        if(op.back->data == '('){
            valid = false;
            break;
        }else{
            postfix.pushback(op.back->data);
            op.popback();
        }
    }
    
    if(num_count != op_count+1) valid = false;
}


int Stack::calculate(){
    node *tmp = this->back;
    int op1, op2; // front 2, front 1;
    if(tmp!=nullptr){
        if(tmp->data == '+'){
            this->popback();
            op2 = calculate();
            op1 = calculate();
            return op1 + op2;
        }else if(tmp->data == '-'){
            this->popback();
            op2 = calculate();
            op1 = calculate();
            return op1 - op2;
        }else if(tmp->data == '*'){
            this->popback();
            op2 = calculate();
            op1 = calculate();
            return op1 * op2;
        }else if(tmp->data == '/'){
            this->popback();
            op2 = calculate();
            op1 = calculate();
            return op1 / op2;
        }else if(tmp->data >= '0' || tmp->data<='9'){
            int ret = tmp->data - '0';
            this->popback();
            return ret;
        }
    }
    return 0;
}


void Stack::print(){
    node *out = this->front;
    while (out != nullptr) {
        std::cout<<out->data;
        out = out->next;
    }
}


void Stack::clear(){
    while(back != nullptr){
        popback();
    }
}

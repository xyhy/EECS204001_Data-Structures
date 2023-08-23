//
//  main.cpp
//  DS_2020_HW3_Binary Tree
//
//  Created by 顏浩昀 on 2020/11/17.
//

#include <iostream>
#include <string>


class node{
    friend class Tree;
public:
    node():value(0), left(nullptr), right(nullptr), parent(nullptr){};
    node(int val):value(val), left(nullptr), right(nullptr), parent(nullptr){};
private:
    int value;
    node *left, *right, *parent;
};

class Tree{
public:
    node* construct();
    void Preorder(node*);
    void Inorder(node*);
    void Postorder(node*);
    node* DeleteLeaf(node*);
    //void clear(node *root);
    int Height(node*, int);
    int WeightSum(node*, int);
    int MaximumPathSum(node*);
    int BinaryTower(node*);
    bool Foldable(node*, node*);
    node *root = nullptr;
};

std::string input;
int j = 0;
int td = 0; //towerdefense

int main() {
    Tree T;
    while (std::cin>>input) {
        T.root = T.construct();
        std::string cmd;
        int ans;
        while (std::cin>>cmd) {
            if(cmd == "Traverse"){
                T.Preorder(T.root);
                std::cout<<"\n";
                T.Inorder(T.root);
                std::cout<<"\n";
                T.Postorder(T.root);
                std::cout<<"\n";
            }else if(cmd == "Height"){
                ans = T.Height(T.root, 0);
                std::cout<<ans<<"\n";
            }else if(cmd == "WeightSum"){
                ans = T.WeightSum(T.root, 0);
                std::cout<<ans<<"\n";
            }else if(cmd == "MaximumPathSum"){
                ans = T.MaximumPathSum(T.root);
                std::cout<<ans<<"\n";
            }else if(cmd == "BinaryTower"){
                int trash = T.BinaryTower(T.root);
                if(trash == 0){
                    std::cout<<td+1<<"\n";
                }else{
                    std::cout<<td<<"\n";
                }
            }else if(cmd == "DeleteLeaf"){
                T.root = T.DeleteLeaf(T.root);
            }else if(cmd == "Foldable"){
                if(T.Foldable(T.root, T.root))
                    std::cout<<"Yes\n";
                else
                    std::cout<<"No\n";
            }else if(cmd == "End"){
                //T.clear(T.root);
                j = 0;
                td = 0;
                input.clear();
                break;
            }else{
                continue;
            }
        }
    }
    return 0;
}

int num = 0;
int neg = 0;
node *cur = nullptr;
node* Tree::construct(){
    node *rt = nullptr;
    while (j < input.size()) {
        if(input[j] == '('){
            if(rt == nullptr){
                node *n = new node();
                n->parent = cur;
                rt = n;
                j++;
            }else{
                if(rt->left == nullptr){
                    cur = rt;
                    rt->left = construct();
                }
                if(rt->right == nullptr){
                    cur = rt;
                    rt->right = construct();
                }
            }
        }else if(isdigit(input[j]) || input[j] == '-'){
            if(input[j] == '-'){
                neg = 1;
                j++;
            }else{
                num = num*10 + input[j] - '0';
                if(!isdigit(input[j+1])){
                    if(neg){
                        rt->value = num*(-1);
                    }else{
                        rt->value = num;
                    }
                    num = 0;
                    neg = 0;
                }
                j++;
            }
        }else if(input[j] == ')'){
            if(input[j-1] == '('){
                j++;
                return nullptr;
            }else{
                j++;
                return rt;
            }
        }
    }
    return rt;
}

void Tree::Preorder(node *root){
    if(root == nullptr) return;
    else{
        std::cout<<root->value<<" ";
        if(root->left != nullptr)   Preorder(root->left);
        if(root->right != nullptr)  Preorder(root->right);
    }
}
void Tree::Inorder(node *root){
    if(root == nullptr) return;
    else{
        if(root->left != nullptr)   Inorder(root->left);
        std::cout<<root->value<<" ";
        if(root->right != nullptr)  Inorder(root->right);
    }
}
void Tree::Postorder(node *root){
    if(root == nullptr) return;
    else{
        if(root->left != nullptr)   Postorder(root->left);
        if(root->right != nullptr)  Postorder(root->right);
        std::cout<<root->value<<" ";
    }
}

node* Tree::DeleteLeaf(node* rt){
    if(rt == nullptr){
        return nullptr;
    }else if(rt->left == nullptr && rt->right == nullptr){
        delete rt;
        return nullptr;
    }
    rt->left = DeleteLeaf(rt->left);
    rt->right = DeleteLeaf(rt->right);
    return rt;
}
/*
void Tree::clear(node *root){
    if(root->left != nullptr)   clear(root->left);
    if(root->right != nullptr)   clear(root->right);
    std::cout<<root->value<<" ";
    root = nullptr;
    delete root;
}
*/
int Tree::Height(node *root, int h){
    int h_l = 0, h_r = 0;
    if(root == nullptr) return 0;
    else{
        if(root->left != nullptr){
            h_l = Height(root->left, 0);
        }
        if(root->right != nullptr){
            h_r = Height(root->right, 0);
        }
        h = (h_l > h_r) ? h_l+1 : h_r+1;
        return h;
    }
}

int Tree::WeightSum(node *root, int sum){
    int sum_l = 0, sum_r = 0;
    if(root == nullptr) return 0;
    else{
        if(root->left != nullptr)
            sum_l=WeightSum(root->left, 0);
        if(root->right != nullptr)
            sum_r=WeightSum(root->right, 0);
        sum = sum + sum_l + sum_r + root->value;
        return sum;
    }
}

int Tree::MaximumPathSum(node *root){
    int sum = 0;
    int sum_l = 0, sum_r = 0;
    if(root == nullptr) return 0;
    else{
        if(root->left == nullptr || root->right == nullptr){
            if(root->left != nullptr){
                sum = MaximumPathSum(root->left) + root->value;
            }
            else if(root->right != nullptr){
                sum = MaximumPathSum(root->right) + root->value;
            }
            else {
                sum = root->value;
            }
            return sum;
        }else{
            sum_l = MaximumPathSum(root->left);
            sum_r = MaximumPathSum(root->right);
            sum = (sum_l > sum_r) ? sum_l+root->value : sum_r+root->value;
            return sum;
        }
    }
}


int Tree::BinaryTower(node* rt){
    if(rt == nullptr)   return 2;
    else{
        if(rt->left == nullptr && rt->right == nullptr && rt == this->root){
            td++;
            return 2;
        }else if(rt->left == nullptr && rt->right == nullptr){
            return 0;
        }
        int needdef = 0, defed = 0;
        if(rt->left != nullptr){
            int prot = BinaryTower(rt->left);
            if(prot == 0)    needdef = 1;
            if(prot == 1)    defed = 1;
        }
        if(rt->right != nullptr){
            int prot = BinaryTower(rt->right);
            if(prot == 0)   needdef = 1;
            if(prot == 1)   defed = 1;
        }
        if(needdef){
            td++;
            return 1;
        }
        if(defed){
            return 2;
        }
        return 0;
    }
}

bool Tree::Foldable(node* ltree, node* rtree){
    if(ltree == nullptr && rtree == nullptr){
        return true;
    }
    else{
        if( (ltree->left == nullptr && rtree->right != nullptr) || (ltree->right == nullptr && rtree->left != nullptr) || (ltree->left != nullptr && rtree->right == nullptr) || (ltree->right != nullptr && rtree->left == nullptr) )   return false;
        
        if(ltree->left == nullptr && rtree->right == nullptr && ltree->right == nullptr && rtree->left == nullptr){
            return true;
        }
        
        if((ltree->left != nullptr && rtree->right != nullptr) || (ltree->right != nullptr && rtree->left != nullptr) ){
            return Foldable(ltree->left, rtree->right) && Foldable(ltree->right, rtree->left);
        }
        return true;
    }
}

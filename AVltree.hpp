#ifndef AVLTREE_H
#define AVLTREE_H


#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <math.h>
#include <algorithm>
#include <optional>
#include <limits>
#include <set>
#include <queue>
#include <assert.h>
#include "BinarySearchTree.hpp"


using namespace std;

template<class t>
class AVLTree : public BinarySearchTree <t>{
    private:
        struct AvlNode{
            t data;
            int hight{0};
            AvlNode* right{nullptr};
            AvlNode* left{nullptr};
            AvlNode(const t& x) : data(x), left(nullptr), right(nullptr) {}
            AvlNode(AvlNode* node) : data(node ? node->data : t()),
                                   left(node && node->left ? new AvlNode(node->left) : nullptr),
                                   right(node && node->right ? new AvlNode(node->right) : nullptr) {}


            bool operator==(const AvlNode& other) const { return data == other.data; }

        };

        AvlNode* root{nullptr};
        int nodecount{0};

        int ch_hight_helper(AvlNode*node)const{
            if(!node)
                return -1;
            return node->hight;
        }
        void update_hieght_helper(AvlNode*node){
            node->hight=1+max(ch_hight_helper(node->left),ch_hight_helper(node->right));
        }
        int balance_f_h(AvlNode*node)const{
            return ch_hight_helper(node->left)-ch_hight_helper(node->right);
        }
        
        AvlNode*Right_rot_h(AvlNode*node){
            AvlNode*root=node->left;
            node->left=root->right;
            root->right=node;
            update_hieght_helper(root);
            update_hieght_helper(node);
            return root;
        }
        AvlNode* left_rot_h(AvlNode* node) {
            AvlNode* root = node->right;   
            node->right = root->left;      
            root->left = node;             

            
            update_hieght_helper(node);
            update_hieght_helper(root);

            return root; 
        }

        AvlNode* Balance_h(AvlNode*node){
            if(balance_f_h(node)==2){
                if(balance_f_h(node->left)==-1)
                    node->left=left_rot_h(node->left);
                node=Right_rot_h(node);
            }
            else if(balance_f_h(node)==-2){
                if(balance_f_h(node->left)==1)
                    node->right=Right_rot_h(node->right);
                node=left_rot_h(node);

            }
            return node;
        }
        AvlNode* insert_h(t target,AvlNode* node){
            if(target<node->data){
                if(!node->left)
                    node->left=new AvlNode(target);
                else
                    insert_h(target,node->left);
                
            }
            else if(target>node->data){
                if(!node->right)
                    node->right=new AvlNode(target);
                else
                    insert_h(target,node->right);
            }
            update_hieght_helper(node);
            return Balance_h(node);
        }
         void clear(AvlNode* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
    AvlNode*del_h(t target , AvlNode* node){
        if(!node)
            throw runtime_error("Empty tree");
        if(target<node->data)
            node->left=del_h(target,node->left);
        else if (target>node->data)
            node->right=del_h(target,node->right);
        else{
            if(! node->left && ! node->right){
                delete node;
                return nullptr;
            }
            else if(! node->left){
                AvlNode*tmp=node->right;
                delete node;
                return tmp;
            }
            else if(! node->right){
                AvlNode*tmp=node->left;
                delete node;
                return tmp;
            }
            else{
                AvlNode*mn=MinH(node->right);
                node->data=mn->data;
                del_h(mn->data,node->right);
            }


        }
        if(node){
            update_hieght_helper(node);
            Balance_h(node);
        }
        return node;
    }

    public:

        void inserter(t target)override{
            if(! this->root)
                root=new AvlNode(target);
            else
                this->root=insert_h(target,this->root);

        }
        void deldelet_val(t x) override{
            try
            {
                root=del_h(x,this->root);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
        }
        


};

#endif
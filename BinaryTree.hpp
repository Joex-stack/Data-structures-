#ifndef BINARYTREE_H
#define BINARYTREE_H


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>

using namespace std;



template<class t>
class BinaryTree{
    private:
        
        class TreeNode {
        public:
            t data;
            TreeNode *left{nullptr};
            TreeNode *right{nullptr};

            TreeNode(t x) : data(x), left(nullptr), right(nullptr) {}


            TreeNode(t x, TreeNode *l, TreeNode *r) : data(x), left(l), right(r) {}


            TreeNode(TreeNode*node){
                if (!node) {  // defensive check
                    this->data = t();   
                    this->left = nullptr;
                    this->right = nullptr;
                    return;
                }


                this->data=node->data;
                this->left  = node->left  ? new TreeNode(node->left)  : nullptr;
                this->right = node->right ? new TreeNode(node->right) : nullptr;
            }
            bool operator==(const TreeNode& other) const {
                return this->data == other.data;
            }
        };
        TreeNode* head;
        int hight{0};
        int nodecount{0};
        


        void printnVLR(TreeNode* node) const {
            if (!node) return;
            cout << node->data << endl;
            printnVLR(node->left);
            printnVLR(node->right);
        }

        void printnLVR(TreeNode* node)const  {
            if (!node) return;
            printnLVR(node->left);
            cout << node->data << endl;
            printnLVR(node->right);
        }
        bool isValidDirection(const string& s)const  {
            for (char c : s) {
                if (c != 'L' && c != 'R'&&c != 'l'&&c != 'r') {
                    return false;
                }
            }
            return true;
        }
        t maxx(TreeNode* node) const {
            if (!node) 
                throw runtime_error("Empty tree!");

            t maximum = node->data;

            if (node->left) 
                maximum = max(maximum, maxx(node->left));

            if (node->right) 
                maximum = max(maximum, maxx(node->right));

            return maximum;
        }
        bool is_in(TreeNode* node,t x)const {
            if(!node){
                return false;
            }
            bool ans=false;
            if(node->data==x){
                ans=true;
                return ans;
            }
            if(node->left){
                ans=ans||is_in(node->left,x);
            }
            if(node->right){
                ans=ans||is_in(node->right,x);
            }
            return ans;
        }
        bool is_binary(TreeNode* node) const {
            if (node->left == nullptr && node->right == nullptr)
                return true;
            if (node->left != nullptr && node->right != nullptr)
                return true;
            return false;
        }

        bool is_bb(TreeNode*node)const {
            if(not node)
                return true;

             bool ans=is_binary(node);
            if(node->left)
                ans=ans&&is_bb(node->left);
            if(node->right)
                ans=ans&&is_bb(node->right);
            return ans;
            
        }
        void printnlift(TreeNode*node)const {
            if(!node)return;
            printnlift(node->left);
            cout<<node->data<<endl;
        }
        int len(TreeNode*node)const{
            int ans =1;
            if(node->left){
                ans+=len(node->left);
            }
            if(node->right){
                ans =max(ans,len(node->right));
            }
            return ans;

        }
        void clear(TreeNode* node) {
            if (!node) return;
            clear(node->left);   
            clear(node->right);  
            delete node;         
        }
        bool is_cmp( TreeNode*&node) const{
            bool ans=true;
            if(node->left && !node->right)
                ans=false;
            if(! node->left && node->right)
                ans=false;
            if(ans&&node->left){
                ans=ans&&is_cmp(node->left);
            }
            if(ans&&node->right)
                ans=ans&&is_cmp(node->right);
            return ans;
        }
        TreeNode* buildPerfectTree4() {
            TreeNode* n1  = new TreeNode(1);
            TreeNode* n2  = new TreeNode(2);
            TreeNode* n3  = new TreeNode(3);
            TreeNode* n4  = new TreeNode(4);
            TreeNode* n5  = new TreeNode(5);
            TreeNode* n6  = new TreeNode(6);
            TreeNode* n7  = new TreeNode(7);
            TreeNode* n8  = new TreeNode(8);
            TreeNode* n9  = new TreeNode(9);
            TreeNode* n10 = new TreeNode(10);
            TreeNode* n11 = new TreeNode(11);
            TreeNode* n12 = new TreeNode(12);
            TreeNode* n13 = new TreeNode(13);
            TreeNode* n14 = new TreeNode(14);
            TreeNode* n15 = new TreeNode(15);

            n1->left = n2;  n1->right = n3;
            n2->left = n4;  n2->right = n5;
            n3->left = n6;  n3->right = n7;
            n4->left = n8;  n4->right = n9;
            n5->left = n10; n5->right = n11;
            n6->left = n12; n6->right = n13;
            n7->left = n14; n7->right = n15;

            return n1; // root
        }
        int construct(TreeNode*&node,deque<t>&pre,deque<t>&in,int start=0,int end=-1){
            if(pre.empty()) return 0 ;          
    
            if(end==-1) end = (int)in.size()-1;

            node=new TreeNode(pre[0]);
            int nodec=1;

            pre.pop_front();

            for(int i=start;i<=end;++i){
                if(node->data==in[i]){
                    if(start<i){
                        nodec+=construct(node->left,pre,in,start,i-1);
                    }
                    if(end>i){
                       nodec+= construct(node->right,pre,in,i+1,end);
                    }
                    break;
                }
            }
            return nodec;

        }
        int constructbinary(TreeNode*&node,deque<pair<t,bool>>&pre){
            if(pre.empty()) return 0;          
            node=new TreeNode(pre.front().first);
            int nodec=1;
            pair<t,bool> p=pre[0];
            pre.pop_front();
            if(not p.second){
                if(pre.size())
                    nodec+=constructbinary(node->left,pre);
                if(pre.size())
                    nodec+=constructbinary(node->right,pre);
            }
            return nodec;
        }
        string ser(TreeNode* node) {
            if (!node) return "()";  

            string s;
            s += '(' + to_string(node->data);
            
            if (node->left)
                s += ser(node->left);
            else
                s += "()";
            
            if (node->right)
                s += ser(node->right);
            else
                s += "()";
            
            s += ')';
            return s;
}
        bool issym(TreeNode* node, TreeNode* nd=nullptr, bool first=true) {
            if (first) { 
                if (!node) return true; 
                return issym(node->left, node->right, false);
            }

            if (!node && !nd) return true;    
            if (!node || !nd) return false;   
            if (node->data != nd->data) return false; 

            return issym(node->left, nd->right, false) &&
                issym(node->right, nd->left, false);
}



    public:
        BinaryTree():head(new TreeNode(t())){}

        BinaryTree(t x): head(new TreeNode(x)){nodecount++;}

        BinaryTree(deque<t>&pre,deque<t>&in){
           this->nodecount= construct(this->head);
        }

        BinaryTree(const BinaryTree& tree){
            this->head=new TreeNode(tree.head);
        }
        BinaryTree(deque<pair<t,bool>>&pre){
            this->nodecount=constructbinary(this->head,pre);

        }

        BinaryTree operator=(const BinaryTree& other){
            if(other==this)return *this;
            clear(this->head);
            this->head=other.head ? new TreeNode(other.head) : nullptr;
            return *this;
        }
        void add(const initializer_list<t>&x,const string&direction){
            string dir=direction;
            if(x.size()==0){
                throw runtime_error("Empty List");
            }
            if(direction.size()==0){
                throw runtime_error("Empty Direction");
            }
            if(not isValidDirection(dir)){
                throw runtime_error("Invalid Direction");
            }
            TreeNode*node=head;
            auto it = x.begin();
            int lh=0,rh=0;
            for (size_t i = 0; i < direction.size() && it != x.end(); i++ ) {
                if (direction[i] == 'L' || direction[i] == 'l' ) {
                    if(node->left==nullptr){
                        node->left = new TreeNode(*it); 
                        it++;
                        nodecount++;
                    }
                    node = node->left;
                } else {
                    if(node->right==nullptr) {
                        node->right = new TreeNode(*it);
                        it++;
                        nodecount++;
                    }
                    node = node->right;
                }
            }

            
            
            
            

            
        }
       t max_element_tree() const {
            if (!this->head)
                throw runtime_error("Tree is empty!");
            return maxx(this->head);
        }
        int tree_hight() const {
            return this->len(this->head);
            
        }
        int tree_level()const{
            return len(this->head)-1;
        }
        bool is_exist(t x) const {
            return is_in(this->head,x);
        }
        bool is_perfect() const {
            return is_bb(this->head);
        }
        bool is_compelete() {
            return is_cmp(this->head);
        }
        int NodeCount()const {
            return this->nodecount;
        }
        void printlifts() const {
            printnlift(this->head);

        }
        void PrintbyLvl()const{
            queue<TreeNode*>q;
            q.push(this->head);
            int lvl=0;
            while (!q.empty())
            {
                cout<<"Level "<<lvl<<": ";
                int sz=q.size();
                while(sz--){
                TreeNode*curr=q.front();
                q.pop();

                cout<<curr->data<<" , ";
                if(curr->left)
                    q.push(curr->left);
                if(curr->right)
                    q.push(curr->right);
            }
            cout<<endl;
            lvl++;
        }}
        void PrintLVL_spi(){
            queue<TreeNode*>q;
            q.push(this->head);
            int lvl=0;
            while (!q.empty())
            {
                cout<<"Level "<<lvl<<": ";
                int sz=q.size();
                vector<t>vals;
                while(sz--){
                
                    TreeNode*curr=q.front();
                    q.pop();

                    vals.push_back(curr->data);
                    if(curr->left)
                        q.push(curr->left);
                    if(curr->right)
                        q.push(curr->right);
            
             
        }
            if (lvl % 2 == 0) {
                for (int x : vals) 
                    cout << x << " , ";
        }   
            else {
                for (int i = vals.size()-1; i >= 0; i--) 
                    cout << vals[i] << " , ";
            }
            cout<<endl;
            lvl++; 
            
        }}
            


        
        
            
            
        
        void gettest(){
            this->head=this->buildPerfectTree4();
        }
        vector<vector<t>>getlvlvec()const {
            vector<vector<t>>lvldata;
            queue<TreeNode*>q;
            q.push(head);
            while(! q.empty()){
                vector<t>lvl;
                int sz=q.size();
                while (sz--)
                {
                    TreeNode*curr=q.front();
                    q.pop();
                    lvl.push_back(curr->data);
                    if(curr->left){
 
                    q.push(curr->left);
                }
                    if(curr->right){

                    q.push(curr->right);
                }
                }
                lvldata.push_back(lvl);
                


            }
            return lvldata;

            
        }

        vector<t>getflatten()const {
            auto vec=this->getlvlvec();
            vector<t>v;
            for(const auto&vv:vec){
                for(const auto &x:vv){
                    v.push_back(x);
                }
            }
            return v;
        }
        string serializasion(){
            return ser(this->head);
        }
        bool is_symetric(){
            return issym(this->head);
        }
        
        void printTreeLVR()const {
            printnLVR(this->head);
        }
        void printTreeVLR()const {
            printnVLR(this->head);
        }
        ~BinaryTree(){
            clear(head);
        }

};

#endif
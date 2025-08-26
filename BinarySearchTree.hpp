#ifndef BINARYSEARHTREE_H
#define BINARYSEARHTREE_H

#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <optional>
#include <limits>

using namespace std;

template<class t>
class BinarySearchTree {
private:
    struct TreeNode {
        t data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(const t& x) : data(x), left(nullptr), right(nullptr) {}
        TreeNode(TreeNode* node) : data(node ? node->data : t()),
                                   left(node && node->left ? new TreeNode(node->left) : nullptr),
                                   right(node && node->right ? new TreeNode(node->right) : nullptr) {}


        bool operator==(const TreeNode& other) const { return data == other.data; }
    };

    TreeNode* head{nullptr};
    int nodecount{0};

    bool searchH(TreeNode* node, const t& x) const {
        if (!node) return false;
        if (x == node->data) return true;
        return x < node->data ? searchH(node->left, x) : searchH(node->right, x);
    }
    TreeNode* searchHN(TreeNode* node, const t& x) const {
        if (!node) return nullptr;
        if (x == node->data) return node;
        return x < node->data ? searchH(node->left, x) : searchH(node->right, x);
    }

    bool insertH(TreeNode*& node, const t& x) {
        if (!node) { node = new TreeNode(x); return true; }
        if (x == node->data) return false;
        if (x < node->data) return insertH(node->left, x);
        return insertH(node->right, x);
    }

    TreeNode* MinH(TreeNode* node) const {
        if (!node) throw runtime_error("Empty tree");
        while (node->left) node = node->left;
        return node;
    }

    t MaxH(TreeNode* node) const {
        if (!node) throw runtime_error("Empty tree");
        while (node->right) node = node->right;
        return node->data;
    }

    static bool validate(TreeNode* node, optional<t> lo, optional<t> hi) {
        if (!node) return true;
        if (lo && !( *lo < node->data )) return false;
        if (hi && !( node->data < *hi )) return false;
        return validate(node->left, lo, optional<t>(node->data)) &&
               validate(node->right, optional<t>(node->data), hi);
    }

    static TreeNode* bhelper(const vector<t>& a, int l, int r) {
        if (l > r) return nullptr;
        int mid = l + (r - l) / 2;
        TreeNode* node = new TreeNode(a[mid]);
        node->left  = bhelper(a, l, mid - 1);
        node->right = bhelper(a, mid + 1, r);
        return node;
    }

    TreeNode* LCAH(TreeNode* node, const t& x, const t& y) const {
        if (!node) return nullptr;
        if (node->data >= x && node->data <= y) return node;
        if (node->data <= x && node->data >= y) return node;
        if (node->data > x && node->data > y) return LCAH(node->left, x, y);
        if (node->data < x && node->data < y) return LCAH(node->right, x, y);
        return nullptr;
    }

    void clear(TreeNode* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    string ser(TreeNode* node) const {
        if (!node) return "()";
        string s = "(" + to_string(node->data);
        s += node->left ? ser(node->left) : "()";
        s += node->right ? ser(node->right) : "()";
        s += ")";
        return s;
    }

    bool issym(TreeNode* a, TreeNode* b) const {
        if (!a && !b) return true;
        if (!a || !b) return false;
        if (a->data != b->data) return false;
        return issym(a->left, b->right) && issym(a->right, b->left);
    }

    void printnlift(TreeNode* node) const {
        if (!node) return;
        printnlift(node->left);
        cout << node->data << '\n';
    }

    void printnVLR(TreeNode* node) const {
        if (!node) return;
        cout << node->data << '\n';
        printnVLR(node->left);
        printnVLR(node->right);
    }

    void printnLVR(TreeNode* node) const {
        if (!node) return;
        printnLVR(node->left);
        cout << node->data << '\n';
        printnLVR(node->right);
    }
    void inordert(TreeNode* node, vector<t>& v) const {
    if (!node) return;
    inordert(node->left, v);
    v.push_back(node->data);
    inordert(node->right, v);
}
    void  familyH(vector <TreeNode*> &v,TreeNode*node,t x,bool first = false){
        if(not searcher(x) and first )
            return;
        if(not node)
            return;

        v.push_back(node);
        if(x<node->data)
            familyH(v,node->left,x,false);
        else if(x>node->data)
            familyH(v,node->right,x,false);
        else 
            return;

        
    }
    TreeNode*construct(TreeNode*root,vector<t>preorder,int idx,t minele ,t maxele){
        if(idx>preorder.size())
            return nullptr;
        t val=preorder[idx];
        if(val<minele||val>maxele)
            return nullptr;
        root=new TreeNode(val);
        idx++;
        root->left=construct(root->left,preorder,idx,minele,val);
        root->right=construct(root->right,preorder,idx,val,maxele);
        return root;
    }
    TreeNode* delnode(TreeNode* node, t dt) {
    if (!node)
        throw runtime_error("Value not found !");

    if (dt < node->data) {
        node->left = delnode(node->left, dt);
    } 
    else if (dt > node->data) {
        node->right = delnode(node->right, dt);
    } 
    else {
        // Case 1: leaf
        if (!node->left && !node->right) {
            delete node;
            return nullptr;
        }
        // Case 2: one child
        else if (!node->left) {
            TreeNode* temp = node->right;
            delete node;
            return temp;
        } 
        else if (!node->right) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        }
        // Case 3: two children
        else {
            TreeNode* mn = MinH(node->right);
            node->data = mn->data;
            node->right = delnode(node->right, mn->data);
        }
    }
    return node;
}


    
public:
    BinarySearchTree() = default;
    explicit BinarySearchTree(const t& x) : head(new TreeNode(x)), nodecount(1) {}
    BinarySearchTree(const initializer_list<t>& preorder) {
    if (preorder.size() == 0) 
        throw runtime_error("Empty list");
    vector<t> pre(preorder);
    int idx = 0;
    this->head = buildFromPreorder(pre, idx, INT_MIN, INT_MAX);
}

    ~BinarySearchTree() { clear(head); }

    bool inserter(const t& x) {
        if (insertH(head, x)) { ++nodecount; return true; }
        return false;
    }
    vector <TreeNode*> family(t x)const{
        vector <TreeNode*> v;
        familyH(v,this->head,x,true);
        return v;
    }

    pair<bool,t> Anccesstor(t x)const{
        if(not searcher(x))
            throw runtime_error("Element isnt in tree !");
        vector<TreeNode*>v=family(x);
        TreeNode* child=v.back();
        v.pop_back();
        if(child->right)
            return {true , MinH(child->right)};
        TreeNode* anc=v.back();
        v.pop_back();
        while (anc&&anc->right==child&&not v.empty())
        {
            child=anc;
            anc=v.back();
            v.pop_back();
        }
        if(anc)
            return{true ,anc->data};
        else
            return{false,t()};
        

        
    }
    pair<bool,t> Predecessor(t x)const{
        if(not searcher(x))
            throw runtime_error("Element isnt in tree !");
        vector<TreeNode*>v=family(x);
        TreeNode* child=v.back();
        v.pop_back();
        if(child->left)
            return {true , MaxH(child->left)};
        TreeNode* anc=v.back();
        v.pop_back();
        while (anc&&anc->left==child&&not v.empty())
        {
            child=anc;
            anc=v.back();
            v.pop_back();
        }
        if(anc)
            return{true ,anc->data};
        else
            return{false,t()};
        

        
    }

    void delet_val(t x){
        if(not this->head)
            throw runtime_error("Emptu tree !");
        try
        {
            delnode(this->head);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }



    bool searcher(const t& x) const { return searchH(head, x); }

    t Min_ele() const { return MinH(head)->data; }
    t Max_ele() const { return MaxH(head->data); }

    bool search_iter(const t& x) const {
        TreeNode* node = head;
        while (node) {
            if (x == node->data) return true;
            node = (x < node->data) ? node->left : node->right;
        }
        return false;
    }

    static bool is_BST(const BinarySearchTree& bt) {
        return validate(bt.head, nullopt, nullopt);
    }

    static BinarySearchTree build_bst_blncd(const vector<t>& sortedvals) {
        BinarySearchTree bt;
        bt.head = bhelper(sortedvals, 0, (int)sortedvals.size() - 1);
        bt.nodecount = (int)sortedvals.size();
        return bt;
    }

    t LCA(t x, t y) const {
        if (!searcher(x)) throw runtime_error("Frst arg not in tree !");
        if (!searcher(y)) throw runtime_error("second arg not in tree !");
        if (y < x) swap(x, y);
        TreeNode* res = LCAH(head, x, y);
        if (!res) throw runtime_error("LCA not found !");
        return res->data;
    }

    void buidtst() {
        vector<t> v;
        for (int i = 0; i < 10; ++i) v.push_back((t)i);
        clear(head);
        head = bhelper(v, 0, (int)v.size() - 1);
        nodecount = (int)v.size();
    }

    int NodeCount() const { return nodecount; }

    void printlifts() const { printnlift(head); }

    void PrintbyLvl() const {
        if (!head) { cout << "Level 0:\n"; return; }
        queue<TreeNode*> q; q.push(head);
        int lvl = 0;
        while (!q.empty()) {
            cout << "Level " << lvl << ": ";
            int sz = (int)q.size();
            while (sz--) {
                TreeNode* cur = q.front(); q.pop();
                cout << cur->data << " , ";
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
            cout << '\n';
            ++lvl;
        }
    }

    void PrintLVL_spi() const {
        if (!head) { cout << "Level 0:\n"; return; }
        queue<TreeNode*> q; q.push(head);
        int lvl = 0;
        while (!q.empty()) {
            cout << "Level " << lvl << ": ";
            int sz = (int)q.size();
            vector<t> vals;
            vals.reserve(sz);
            while (sz--) {
                TreeNode* cur = q.front(); q.pop();
                vals.push_back(cur->data);
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
            if (lvl % 2 == 0) {
                for (const auto& x : vals) cout << x << " , ";
            } else {
                for (int i = (int)vals.size() - 1; i >= 0; --i) cout << vals[i] << " , ";
            }
            cout << '\n';
            ++lvl;
        }
    }
    vector<t> inorder() const {
        vector<t> v;
        inordert(head, v);
        return v;
    }
    vector<pair<bool,t>>Anccesstor(initializer_list<t>il)const{
        vector<t>v;
        try
        {
            for(auto it=il.begin();it!=il.end();it++){
                v.push_back(Anccesstor(*it));
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }

    string serializasion() const { return ser(head); }
    bool is_symetric() const { return issym(head ? head->left : nullptr, head ? head->right : nullptr); }
    void printTreeLVR() const { printnLVR(head); }
    void printTreeVLR() const { printnVLR(head); }
};


#endif
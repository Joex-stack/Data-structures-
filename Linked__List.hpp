#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <algorithm>

using namespace std;

template <class t>
class LinkedList {
private:
    class Node {
    public:
        t data;
        Node *next;

        Node(t x) : data(x), next(nullptr) {};
        Node(Node *ext, t x) : data(x), next(ext) {};

    };

    Node *head{nullptr};
    Node *tail{nullptr};
    int len = 0;

    void printnodes(const Node *hhead) {
        if (hhead == nullptr) return;
        cout << hhead->data << "\n";
        return printnodes(hhead->next);
    }

    Node *Nfind(Node *hhead, const t &value) {
        if (hhead == nullptr) return nullptr;
        else if (hhead->data == value) return hhead;
        return Nfind(hhead->next, value);
    }

    bool issamn(Node *hhead, Node *hhead2) {
        if (!hhead || !hhead2) return true;
        if (hhead->data != hhead2->data) return false;
        return issamn(hhead->next, hhead2->next);
    }

public:
    LinkedList() = default;
    LinkedList(initializer_list<t> x) {
        this->insert_end(x);
    }
    LinkedList(const LinkedList& other) {
    head = tail = nullptr;
    len = 0;
    Node* curr = other.head;
    while (curr) {
        insert_end(curr->data);  
        curr = curr->next;
    }
}

LinkedList& operator=(const LinkedList& other) {
    if (this == &other) return *this;
    this->~LinkedList();  
    new(this) LinkedList(other);  
    return *this;
}


    void insert_end(t x) {
        Node *node = new Node(x);
        if (!head) head = tail = node;
        else {
            tail->next = node;
            tail = node;
            tail->next = nullptr;
        }
        len++;
    }

    void insert_end(Node *x) {
        if (!head) head = tail = x;
        else {
            tail->next = x;
            tail = x;
            tail->next = nullptr;
        }
        len++;
    }

    void insert_end(initializer_list<t> c) {
        for (const t &x : c) {
            Node *node = new Node(x);
            if (!head) head = tail = node;
            else {
                tail->next = node;
                tail = node;
            }
            len++;
        }
    }

    void printLI() { printnodes(head); }

   t get(int x) const {
        if (x < 0 || x >= len) throw std::out_of_range("Index out of range");
        Node* temp = head;
        for (int i = 0; i < x; ++i) temp = temp->next;
        return temp->data;
}
    Node* getN(int x) const {
        if (x < 0 || x >= len) throw std::out_of_range("Index out of range");
        Node* temp = head;
        for (int i = 0; i < x; ++i) temp = temp->next;
        return temp;
}

    Node *LIfind(t x) {
        Node *val = Nfind(head, x);
        if (val) return val;
        throw runtime_error("Not found , wrong search");
    }

    int LISfind(t x) {
        int val = 0;
        for (Node *temp = head; temp; temp = temp->next) {
            if (temp->data == x) return val;
            val++;
        }
        throw runtime_error("Not found , wrong search");
    }

    int imvLTSfind(t x) {
        int r = 0;
        Node *prev = nullptr;
        for (Node *i = head; i; i = i->next, r++) {
            if (i->data == x) {
                if (!prev) return r;
                swap(prev->data, i->data);
                return r - 1;
            }
            prev = i;
        }
        return -1;
    }

    void updateN(int indx, t x){
        this->getN(indx)->data=x;

    }
    void insert_front(t x) {
    Node* node = new Node(x);
    node->next = head;
    head = node;
    if (!tail) tail = node;
    len++; 
}
    

    void finsert(t x) {
        Node *z = new Node(x);
        z->next = head;
        head = z;
        len++;
    }

    void fdel() {
        if (!head) return;
        Node *temp = head;
        head = head->next;
        delete temp;
        len--;
        if (!head) tail = nullptr;
    }
    

    auto getfrb(int x) {
        if (x >= len) throw out_of_range("Out of range");
        if (!x) return tail->data;
        int z = len - 1 - x;
        Node *i = head;
        while (z--) i = i->next;
        return i->data;
    }

    int getlen() const  { return len; }
    Node *gethead() const { return head; }

    bool issameLIP(const LinkedList<t> li) {
        if (len != li.len) return false;
        return issamn(head, li.head);
    }

    bool issameLI(LinkedList<t> li) {
        return issamn(head, li.gethead());
    }

    void del(int indx) {
        if (indx < 0 || indx >= len) throw out_of_range("Index out of range");
        Node *curr = head;
        Node *prev = nullptr;
        for (int i = 0; i < indx; ++i) {
            prev = curr;
            curr = curr->next;
        }
        if (!prev) {
            head = curr->next;
            if (curr == tail) tail = nullptr;
        } else {
            prev->next = curr->next;
            if (curr == tail) tail = prev;
        }
        delete curr;
        len--;
    }

    void DelWithKey(t x) {
        Node *prev = nullptr;
        for (Node *curr = head; curr; curr = curr->next) {
            if (curr->data == x) {
                if (!prev) {
                    head = head->next;
                    delete curr;
                    len--;
                    return;
                } else {
                    prev->next = curr->next;
                    if (curr == tail) tail = prev;
                    delete curr;
                    len--;
                    return;
                }
            }
            prev = curr;
        }
    }

    void SwapLI() {
        if (len <= 1) return;
        int mid = len / 2;
        int c = 0;
        for (Node *f = head; f && f->next;) {
            if (len % 2 == 1 && c == mid) {
                f = f->next;
                c++;
                continue;
            }
            swap(f->data, f->next->data);
            f = f->next->next;
            c += 2;
        }
    }

    void sortList() {
        if (!head || !head->next) return;
        vector<t> vals;
        for (Node *curr = head; curr; curr = curr->next)
            vals.push_back(curr->data);
        sort(vals.begin(), vals.end());
        Node *curr = head;
        for (const t &val : vals) {
            curr->data = val;
            curr = curr->next;
        }
    }

    void swapht() {
        if (len <= 1) return;
        Node *temp = head;
        Node *prev = nullptr;
        for (Node *curr = head; curr; curr = curr->next) {
            if (curr == tail) {
                if (prev) prev->next = head;
                head = tail;
                tail = temp;
                tail->next = nullptr;
                return;
            }
            prev = curr;
        }
    }

    void uniqueLI() {
        if (len <= 1) return;
        sortList();
        Node *prev = head;
        int i = 1;
        for (Node *curr = head->next; curr;) {
            if (curr->data == prev->data) {
                del(i);
                curr = prev->next;
                len--;
            } else {
                prev = curr;
                curr = curr->next;
                ++i;
            }
        }
    }

    void DelLOcc(t x) {
        if (len <= 1) return;
        sortList();
        Node *prev = head;
        int i = 1;
        for (Node *curr = head->next; curr;) {
            if (curr->data == prev->data && curr->data == x && (!curr->next || curr->next->data != x)) {
                del(i);
                curr = prev->next;
            } else {
                prev = curr;
                curr = curr->next;
                ++i;
            }
        }
    }

    t Max() {
        if (!head) throw runtime_error("Empty list");
        t mx = head->data;
        for (Node *curr = head->next; curr; curr = curr->next)
            if (curr->data > mx) mx = curr->data;
        return mx;
    }

    void Combine(LinkedList<t> &other) {
        Node *tmp = head;
        Node *tmp2 = other.gethead();
        Node *n1, *n2;

        while (tmp && tmp2) {
            n1 = tmp->next;
            n2 = tmp2->next;
            tmp->next = tmp2;
            tmp2->next = n1;
            tmp = n1;
            tmp2 = n2;
            
        }

        if (!tmp && tmp2) {
            while (tmp2) {
                insert_end(tmp2->data);
                tmp2 = tmp2->next;
                
            }
            
        }

        this->len+=other.getlen();

        other.head = nullptr;
        other.tail = nullptr;
        other.len = 0;
    }

    ~LinkedList() {
        Node *curr = head;
        while (curr) {
            Node *next = curr->next;
            delete curr;
            curr = next;
        }
        head = tail = nullptr;
        len = 0;
    }
};


template <class t>
class tLinkedList  
 {
private:
    class Node {
    public:
        t data;
        Node *next;
        Node* prev;

        Node(t x) : data(x), next(nullptr) {};
        Node(Node* rev,Node *ext, t x) : data(x), next(ext),prev(rev) {};
        void set(Node* rev,Node *ext){
            this->prev=rev;
            this->next=ext;
        }
        static void  link(Node* &fst,Node *&second){
           if(fst) fst->next =second;
           if(second) second->prev=fst;

        }

        

        ~Node() {
            next = nullptr;
            data = t();
        }
    };

    Node *head{nullptr};
    Node *tail{nullptr};
    int len = 0;

    void printnodes(const Node *hhead) {
        if (hhead == nullptr) return;
        cout << hhead->data << "\n";
        return printnodes(hhead->next);
    }

    Node *Nfind(Node *hhead, const t &value) {
        if (hhead == nullptr) return nullptr;
        else if (hhead->data == value) return hhead;
        return Nfind(hhead->next, value);
    }

    bool issamn(Node *hhead, Node *hhead2) {
        if (!hhead || !hhead2) return true;
        if (hhead->data != hhead2->data) return false;
        return issamn(hhead->next, hhead2->next);
    }

    public:
    tLinkedList() = default;
    tLinkedList(initializer_list<t> x) {
        this->insert_end(x);
    }
    tLinkedList(const tLinkedList& other) : head(nullptr), tail(nullptr), len(0) {
    for (Node* curr = other.head; curr; curr = curr->next) {
        insert_end(curr->data);
    }
}
    tLinkedList& operator=(const tLinkedList& other) {
        if (this != &other) {
            while (head) fdel(); // Clear current list
            for (Node* curr = other.head; curr; curr = curr->next) {
                insert_end(curr->data);
        }
    }
    return (*this);
}
    void insert_end(t x){
        Node* node=new Node(x);
        if(!head){
            head =tail=node;
        }
        else{
            Node::link(tail,node);
            tail=node;
            
        }
        len++;
    }
    void finsert(t x){
    Node* node = new Node(x);

    if (head) {
        Node::link(node, head); 
        head = node;
    } else {
        head = tail = node;
    }
    len++;
}


    void fdel(){
        if(!head) return;
        auto x= head;
        head=head->next;
        if(head)head->prev=nullptr;
        delete x;
        len--;
        if(!len) tail=nullptr;
    }
    void edel() {
    if (!tail) return;

    Node* tmp = tail;
    if (tail == head) {
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr; 
    }
    delete tmp;
    len--;
}



    void del(int indx){
        int i=0;
        if (indx < 0 || indx >= len) {
           throw std::out_of_range("Invalid index");
}
        for(Node* curr=this->head;curr;++i){
            if(indx==i){
                if(curr==head){
                    this->fdel();
                    return;
                }
                else if(curr==tail) {
                    this->edel();
                    return;
                }
                Node* tmp=curr;
                // curr=curr->next;
                link(curr->prev,curr->next);
                len--;
                tmp->next=nullptr;
                tmp->prev=nullptr;
                
                delete tmp;
                tmp=nullptr; 
                return;
            }
            curr=curr->next;
        }
    }
    void sortList() {
        if (!head || !head->next) return;
        vector<t> vals;
        for (Node *curr = head; curr; curr = curr->next)
            vals.push_back(curr->data);
        sort(vals.begin(), vals.end());
        Node *curr = head;
        for (const t &val : vals) {
            curr->data = val;
            curr = curr->next;
        }
    }
     t Max() {
        if (!head) throw runtime_error("Empty list");
        t mx = head->data;
        for (Node *curr = head->next; curr; curr = curr->next)
            if (curr->data > mx) mx = curr->data;
        return mx;
    }
    void uniqueLI() {
        if (len <= 1) return;
        sortList();
        Node *prev = head;
        int i = 1;
        for (Node *curr = head->next; curr;) {
            if (curr->data == prev->data) {
                del(i);
                curr = prev->next;
                len--;
            } else {
                prev = curr;
                curr = curr->next;
                ++i;
            }
        }
    }
     t get(int x) const {
        if (x < 0 || x >= len) throw std::out_of_range("Index out of range");
        Node* temp = head;
        for (int i = 0; i < x; ++i) temp = temp->next;
        return temp->data;
}
    t getfrb  (int x) const {
    if (x >= len || x < 0)
        throw out_of_range("Index out of range");

    if (x == 0) {
        if (!tail) 
            throw runtime_error("Tail is null — list is empty");
        return tail->data;
    }

    int z = len - 1 - x;
    Node* i = head;
    while (z--) {
        if (!i) 
            throw runtime_error("Null pointer while traversing");
        i = i->next;
    }
    return i->data;
}





    int getlen() const  { return len; }
    Node *gethead() const { return head; }


};


template <class t>
class ArrayLI{

    private: 
        LinkedList<pair<t,int>> data;
        int size;
    public :
        ArrayLI(int sz):size(sz){}
        ArrayLI(const ArrayLI& other) : size(other.size), data(other.data) {}


ArrayLI& operator=(const ArrayLI& other) {
    if (this != &other) {
        size = other.size;
        data = other.data;
    }
    return *this;
}

        void set_value(t d, int indx) {
    if (indx < 0 || indx >= size) {
        throw std::out_of_range("Index out of range");
    }
    for (int j = 0; j < data.getlen(); j++) {
        if (data.get(j).second == indx) {
            data.del(j);
            break;
        }
    }
    data.insert_end(make_pair(d, indx));
}
        vector<t> getdatavec() const {
            vector<t> datavec(size, 0.0);
            for (int j = 0; j < data.getlen(); j++) {
                auto p = data.get(j);
                if (p.second >= 0 && p.second < size) {
                    datavec[p.second] = p.first;
                }
            }
            return datavec;
        }

        void update_sets(t d, int indx) {
        if (indx < 0 || indx >= size) {
            throw std::out_of_range("Index out of range");
        }
        for (int i = 0; i < data.getlen(); i++) {
            if (data.get(i).second == indx) {
                data.getN(i)->data = make_pair(d, indx);
                return;
            }
        }
        data.insert_end(make_pair(d, indx));
    }

        void printall() const {
    for (int i = 0; i < size; i++) {
        bool found = false;
        for (int j = 0; j < data.getlen(); j++) {
            if (data.get(j).second == i) {
                cout << data.get(j).first << " ";
                found = true;
                break; 
            }
        }
        if (!found) cout << 0.0 << " ";
    }
    cout << endl;
}

        void printnonz() const {
    for (auto* curr = data.gethead(); curr; curr = curr->next) {
        cout <<"("<< curr->data.first << ","<<curr->data.second<<" ) ";
    }
    cout << endl;
}

    t get(int indxs) const{
        if (indxs < 0 || indxs >= size) {
           throw std::out_of_range("Index out of range");
}
        for(auto* curr =this->data.gethead();curr;curr = curr->next){
            if(curr->data.second==indxs){
                return curr->data.first;
            }
        }
        return 0.0;
    }

    

};



template <class t>
class Matrix {
private:
    LinkedList<ArrayLI<t>> data;
    int rownum;
    int clmnum;
public:
    Matrix(int x, int y) : rownum(x), clmnum(y) {
        if (x < 0 || y < 0) {
            throw std::invalid_argument("Matrix dimensions must be non-negative");
        }
        for (int i = 0; i < rownum; ++i) {
            data.insert_end(ArrayLI(clmnum));
        }
    }

    void set_val(t val, int x, int y) {
        if (x < 0 || x >= rownum || y < 0 || y >= clmnum) {
            throw std::out_of_range("Invalid row or column index");
        }
        data.getN(x)->data.set_value(val,y);
    }

    t get(int x, int y) const {
        if (x < 0 || x >= rownum || y < 0 || y >= clmnum) {
            throw std::out_of_range("Invalid row or column index");
        }
        return data.get(x).get(y);
    }

    void printall() const {
        for (int i = 0; i < rownum; ++i) {
            cout << "Row " << i << ": ";
            data.get(i).printall();
        }
    }

    void printnonz() const {
        for (int i = 0; i < rownum; ++i) {
            cout << "Row " << i << ": ";
            data.get(i).printnonz();
        }
    }
};


#endif // LINKEDLIST_H

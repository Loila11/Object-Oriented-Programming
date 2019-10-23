#include <iostream>
using namespace std;

template <typename T> class Node;
template <typename T> class List;
template <typename T> class Set;
class Pair;

//**********************************************************************************************************************
template <typename T>
class Node {
public:
    T val{};
    Node *next{};

    friend istream & operator >> (istream &in, Node &node) {
        in >> node.val;
        return in;
    }

    friend ostream & operator << (ostream &out, Node &node) {
        out << node.val;
        return out;
    }

public:
    Node operator + (const Node &node) {
        Node<T> rez{};
        rez.val = node.val + this->val;
        return rez;
    }

    Node operator * (const Node &node) {
        Node rez{};
        rez.val = this->val * node.val;
        return rez;
    }

    Node &operator += (const Node &node) {
        *this = *this + node;
        return *this;
    }

    Node &operator = (const Node &node) {
        this->val = node.val;
        return *this;
    }

    bool operator < (const Node &node) const {
        return this->val < node.val;
    }

    bool operator == (const Node &node) const {
        return this->val == node.val;
    }

    bool operator != (const Node &node) const {
        return this->val != node.val;
    }

    ~Node() {
        delete [] next;
    }
};

//**********************************************************************************************************************
template<typename T>
class List {
public:
    int n{};
    Node<T> *start{}, *end{};

    friend ostream & operator << (ostream &out, List &list) {
        for (auto *node = list.start; node != NULL; node = node->next) {
            out << *node << ' ';
        }
        return out;
    }

    friend istream & operator >> (istream &in, List &list) {
        in >> list.n;

        for (int i = 0; i < list.n; i ++) {
            auto *node = new Node<T>;
            in >> *node;
            add_node(node, list);
        }
        return in;
    }

    bool operator == (const List &set) const {
        if (this->n != set.n) {
            return false;
        }

        auto node2 = set.start;
        for (auto node1 = this->start; node1 !=NULL; node1 = node1->next, node2 = node2->next) {
            if (*node1 != *node2) {
                return false;
            }
        }
        return true;
    }

    bool operator != (const List &set) const {
        return !(*this == set);
    }

    bool operator < (const List &set) const {
        if (this->n < set.n) {
            return true;
        } else if (this->n > set.n) {
            return false;
        }

        auto node2 = set.start;
        for (auto node1 = this->start; node1 !=NULL; node1 = node1->next, node2 = node2->next) {
            if (*node2 < *node1) {
                return false;
            }
        }
        return true;
    }

    List &operator = (const List & set) {
        this->n = set.n;

        for (auto node = set.start; node != NULL; node = node->next) {
            add_node(node, *this);
        }
        return *this;
    }

    void sort();
};

template <typename T>
void List<T>:: sort() {
    for (auto  node1 = this->start; node1 != NULL ; node1 = node1->next) {
        for (auto node2 = node1->next; node2 != NULL; node2 = node2->next) {
            if (*node2 < *node1) {
                swap(node1->val, node2->val);
            }
        }
    }
}

template <typename T>
void add_node(Node<T> *node, List<T> &list) {
    if (list.start == NULL) {
        list.start = node;
        list.end = list.start;
    } else {
        list.end->next = node;
        list.end = list.end->next;
    }
}

//**********************************************************************************************************************
template <typename T>
class Set : public List<T> {
public:
    void transform();

    Set operator + (const Set &set) {
        Set<T> rez{};

        copy_object(this->start, rez);
        copy_object(set.start, rez);

        rez.transform();
        return rez;
    }

    Set operator * (const Set &set) {
        Node<T> *node1 = this->start, *node2 = set.start;
        Set rez{};

        while (node1 != NULL && node2 != NULL) {
            if (*node1 < *node2) {
                node1 = node1->next;
            } else if (*node2 < *node1) {
                node2 = node2->next;
            } else {
                auto *aux = new Node<T>;
                aux->val = node1->val;
                add_node(aux, rez);
                node1 = node1->next;
                node2 = node2->next;
                rez.n ++;
            }
        }

        rez.transform();
        return rez;
    }

    Set operator - (const Set &set) {
        Set<T> rez{};
        Node<T> *node1 = this->start, *node2 = set.start;

        while (node1 != NULL) {
            if (node2 == NULL || *node1 < *node2) {
                auto *aux = new Node<T>;
                aux->val = node1->val;
                add_node(aux, rez);
                node1 = node1->next;
                rez.n ++;
            } else if (*node2 < *node1) {
                node2 = node2->next;
            } else{
                node1 = node1->next;
                node2 = node2->next;
            }
        }

        return rez;
    }
};

template <typename T>
void Set<T>::transform() {
    (*this).sort();
    for (auto node = this->start; node != NULL; node = node->next) {
        while (node->next != NULL && *node == *node->next) {
            node->next = node->next->next;
            this->n --;
        }
    }
}

template <typename T>
void copy_object(Node<T> *node, List<T> &list) {
    while (node != NULL) {
        auto *aux = new Node<T>;
        aux->val = node->val;
        add_node(aux, list);
        node = node->next;
        list.n ++;
    }
}

//**********************************************************************************************************************
class Pair {
public:
    int first, second;
    friend Set<Pair>;

    friend istream &operator >> (istream &in, Pair &pair) {
        in >> pair.first >> pair.second;
        return in;
    }

    friend ostream &operator << (ostream &out, Pair &pair) {
        out << '(' << pair.first << ',' << pair.second << ')';
        return out;
    }

    Pair &operator = (const Pair &pair) {
        this->first = pair.first;
        this->second = pair.second;
        return *this;
    }

    bool operator == (const Pair &pair) const {
        return first == pair.first && second == pair.second;
    }

    bool operator != (const Pair &pair) const {
        return first != pair.first || second != pair.second;
    }

    bool operator < (const Pair &pair) const {
        if (first == pair.first) {
            return second < pair.second;
        }

        return first < pair.first;
    }
};

Set<Pair> create(const Set<int> &ps1, const Set<int> &ps2) {
    Set<Pair> p{};
    for (auto node1 = ps1.start; node1 != NULL; node1 = node1->next) {
        for (auto node2 = ps2.start; node2 != NULL; node2 = node2->next) {
            auto pair = new Node<Pair>;
            pair->val.first = node1->val;
            pair->val.second = node2->val;
            add_node(pair, p);
        }
    }
    return p;
}

int main() {
    Set<int> set1, set2, set3;
    cin >> set1;
    set1.transform();
    cin >> set2;
    set2.transform();

    cout << "The first set without duplicates: " << set1 << endl;
    cout << "The second set without duplicates: " << set2 << endl;

    Set<int> difference, intersection, reunion;
    intersection = set1 * set2;
    reunion = set1 + set2;
    difference = set1 - set2;

    cout << "Intersection: " << intersection << endl;
    cout << "Reunion: " << reunion << endl;
    cout << "Difference: " << difference << endl;

    Set<Pair> cartesian_product;
    cartesian_product = create(set1, set2);
    cout << "Cartesian product: " << cartesian_product;

    return 0;
}

#include <iostream>
#include <array>
#include <vector>
using namespace std;


// Linked List Class
template <typename T>
class LinkedList {
public:
    // Node Class
    class Node {
    public:
        // Properties
        T data;
        Node *next;
        Node *prev;

        // Constructors
        Node() : data(0), next(nullptr), prev(nullptr) {};

        // CAO
        Node(const T &value) : data(value), next(nullptr), prev(nullptr) {};
    };

    // Properties
    Node *_head;
    Node *_tail;
    int _size;

    // Constructors
    LinkedList() : _head(nullptr), _tail(nullptr), _size(0) {};

    LinkedList(const LinkedList<T> &list) {
        _head = nullptr;
        _tail = nullptr;
        _size = 0;

        Node *listTraverser = list._head;
        while (listTraverser != nullptr) {
            AddTail(listTraverser->data);
            listTraverser = listTraverser->next;
        }
    }

    // CAO
    LinkedList<T> &operator=(const LinkedList<T> &rhs) {
        if (this == &rhs) {
            return *this;
        }

        Clear();

        this->_size = rhs._size;

        Node *rhsTraverser = rhs._head;
        Node *prevPointer = nullptr;
        while (rhsTraverser != nullptr) {
            Node *newNode = new Node(rhsTraverser->data);
            newNode->prev = prevPointer;

            if (prevPointer != nullptr) {
                prevPointer->next = newNode;
            } else {
                _head = newNode;
            }
            prevPointer = newNode;
            rhsTraverser = rhsTraverser->next;
        }
        _tail = prevPointer;
        return *this;
    }



    // Functions

    // AddHead()
    void AddHead(const T &data)
    {
        Node *newNode = new Node(data);
        if (_size == 0) {
            _head = _tail = newNode;
        } else {
            newNode->next = _head;
            _head->prev = newNode;
            newNode->prev = nullptr;
            _head = newNode;
        }
        _size++;
    }

    // AddTail()
    void AddTail(const T &data) {
        Node *newNode = new Node(data);
        if (_size == 0) {
            _head = _tail = newNode;
        } else {
            _tail->next = newNode;
            newNode->prev = _tail;
            newNode->next = nullptr;
            _tail = newNode;
        }
        _size++;
    }

    // AddNodesHead()
    void AddNodesHead(const T *data, unsigned int count) {
        for (unsigned int i = count - 1; i < count; i--) {
            AddHead(data[i]);
        }
    }

    // AddNodesTail()
    void AddNodesTail(const T *data, unsigned int count) {
        for (unsigned int i = 0; i < count; i++) {
            AddTail(data[i]);
        }
    }

    unsigned int NodeCount() const {
        return _size;
    }

    // PrintForward()
    void PrintForward() const
    {
        for (Node *traverser = _head; traverser != nullptr; traverser = traverser->next) {
            cout << traverser->data << endl;
        }
    }

    // PrintReverse()
    void PrintReverse() const {
        for (Node *rev_traverser = _tail; rev_traverser != nullptr; rev_traverser = rev_traverser->prev) {
            cout << rev_traverser->data << endl;
        }
    }

    // Head()
    // Non-Const
    Node *Head() {
        return _head;
    }

    // Const
    const Node *Head() const {
        return _head;
    }

    // Tail()
    // Non-Const
    Node *Tail() {
        return _tail;
    }

    // Const
    const Node *Tail() const {
        return _tail;
    }


    // GetNode()
    // Non-Const
    Node *GetNode(unsigned int index) {
        if (index >= _size) {
            throw std::out_of_range("Index Out of Range!");
        }
        Node *curr = _head;
        for (int count = 0; count < index + 1; count++) {

            if (count == index) {
                return curr;
            } else {
                curr = curr->next;
            }
        }
    }

    // Const
    const Node *GetNode(unsigned int index) const {
        if (index >= _size) {
            throw std::out_of_range("Index Out of Range!");
        }
        Node *curr = _head;
        for (int count = 0; count < index + 1; count++) {

            if (count == index) {
                return curr;
            } else {
                curr = curr->next;
            }
        }
    }


    // operator[]() :
    // Non-Const
    T &operator[](unsigned int index) {
        return GetNode(index)->data;
    }

    // Const
    const T &operator[](unsigned int index) const {
        return GetNode(index)->data;
    }

    // Find()
    // Non-Const
    Node *Find(const T &data) {
        Node *nodeFinder = _head;
        for (int i = 0; i < _size; i++) {
            if (nodeFinder->data == data) {
                return nodeFinder;
            } else {
                nodeFinder = nodeFinder->next;
            }
        }
        return nullptr;
    }

    // Const
    const Node *Find(const T &data) const {
        Node *nodeFinder = _head;
        int x = 0;
        for (int i = 0; i < _size; i++) {
            if (x < 1 & nodeFinder->data == data) {
                x = x + 1;
                return nodeFinder;
            } else {
                nodeFinder = nodeFinder->next;
            }
            return nullptr;
        }
    }

    // FindAll()
    void FindAll(vector<Node *> &outData, const T &value) const {
        Node *nodeMatch = _head;
        for (int i = 0; i < _size; i++) {
            if (nodeMatch->data == value) {
                outData.push_back(nodeMatch);
            }
            nodeMatch = nodeMatch->next;
        }
    }

    // InsertBefore()
    void InsertBefore(Node *node, const T &data) {
        if (node == nullptr) {
            return;
        }

        Node *newNode = new Node(data);
        newNode->next = node;
        newNode->prev = node->prev;

        if (node->prev != nullptr) {
            node->prev->next = newNode;
        }
        if (node->prev == nullptr) {
            _head = newNode;
        }

        node->prev = newNode;
        _size++;
    }

    // InsertAfter()
    void InsertAfter(Node *node, const T &data) {
        // 1) Check if previous node is nullptr
        if (node == nullptr) {
            return;
        }
        // 2) Prepare a newNode
        Node *newNode = new Node(data);
        // 3) Insert newNode after previous
        newNode->prev = node;
        newNode->next = node->next;
        if (node->next != nullptr) {
            node->next->prev = newNode;
        }
        if (node->next == nullptr) {
            _tail = newNode;
        }
        node->next = newNode;
        _size++;
    }

    // InsertAt()
    void InsertAt(const T &data, unsigned int index)
    {
        Node *newNode = new Node(data);
        if (index < 0) {
            throw std::out_of_range("");
        } else if (index == 0) {
            AddHead(data);
        } else {
            Node *insertionTraverser = _head;
            for (unsigned int i = 0; i < index - 1; i++) {
                if (insertionTraverser == nullptr) {
                    throw std::out_of_range(" ");
                } else {
                    insertionTraverser = insertionTraverser->next;
                }
            }
            newNode->next = insertionTraverser->next;
            insertionTraverser->next = newNode;
        }
        _size++;
    }

    // Operator==()
    bool operator==(const LinkedList<T> &rhs) const {
        if (_size != rhs._size) {
            return false;
        }
        Node *nodeTraverser = _head;
        Node *rhsTraverser = rhs._head;

        for (int i = 0; i < _size; i++) {
            if (nodeTraverser->data == rhsTraverser->data) {
                nodeTraverser = nodeTraverser->next;
                rhsTraverser = rhsTraverser->next;
            } else {
                return false;
            }
        }
        return true;
    }

    // RemoveHead()
    bool RemoveHead()
    {
        Node* removalTraverser = _head;
        if (_head == nullptr)
        {
            return false;
        }
        _head = _head->next;
        if (_head == nullptr)
        {
            _head = _tail = nullptr;
        }
        delete removalTraverser;
        _size--;
        return true;

    }
    // RemoveTail()
    bool RemoveTail()
    {
        Node* removalTraverser = _tail;
        if (_tail == nullptr)
        {
            return false;
        }
        _tail = _tail->prev;

        if (_tail == nullptr)
        {
            _tail = _head = nullptr;
        }
        if (_tail != nullptr)
        {
            _tail->next = nullptr;
        }
        delete removalTraverser;
        _size--;
        return true;

    }

    // RemoveAt()
    bool RemoveAt(unsigned int index)
    {
        if (index == 0)
        {
            RemoveHead();
            return true;
        }
        else
        {
            Node* removalTraverser = _head;
            for (unsigned int i = 0; i < index; i++)
            {
                if (removalTraverser == nullptr)
                {
                    return false;
                }
                else
                {
                    removalTraverser = removalTraverser->next;
                }
            }
            removalTraverser->prev->next = removalTraverser->next;
            if (removalTraverser->next != nullptr)
            {
                removalTraverser->next->prev = removalTraverser->prev;
            }
            delete removalTraverser;
            _size--;
            return true;

        }
    }

    // Remove()
    unsigned int Remove(const T& data)
    {
        unsigned int removalCounter = 0;
        Node* current = _head;
        Node* removalTraverser = _head;
        while (current != nullptr)
        {
            if (current->data == data)
            {
                removalTraverser = current;
                current = current->next;
                if (removalTraverser->prev != nullptr)
                {
                    removalTraverser->prev->next = removalTraverser->next;
                }
                if (removalTraverser->next != nullptr)
                {
                    removalTraverser->next->prev = removalTraverser->prev;
                }
                if (_tail == removalTraverser)
                {
                    _tail = removalTraverser->prev;
                }
                if (_head == removalTraverser)
                {
                    _head = removalTraverser->next;
                }
                delete removalTraverser;
                removalCounter++;
                _size--;
            }
            else
            {
                current = current->next;
            }
        }
        return removalCounter;
    }

    // PrintForwardRecursive()
    void PrintForwardRecursive(const Node* node) const
    {
        if (node == nullptr)
        {
            return;
        }
        cout << node->data << endl;
        PrintForwardRecursive(node->next);
    }

    // PrintReverseRecursive
    void PrintReverseRecursive(const Node* node) const
    {
        if (node == nullptr)
        {
            return;
        }
        cout << node->data << endl;
        PrintReverseRecursive(node->prev);
    }

    // Clear()
    void Clear()
    {
        Node* traverser = _head;
        while (traverser != nullptr)
        {
            Node* nextPosition = traverser->next;
            delete traverser;
            traverser = nextPosition;
        }
        _head = nullptr;
        _tail = nullptr;
        _size = 0;
    }



    ~LinkedList()
    {
        Clear();
    }
};



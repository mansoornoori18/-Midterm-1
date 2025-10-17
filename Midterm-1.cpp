#include <iostream>
using namespace std;

// Constants defined but unused here, just placeholders to avoid warnings
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

// DoublyLinkedList class definition
class DoublyLinkedList {
private:
    // Node structure represents each element of the list
    struct Node {
        int data;      // Data stored in the node
        Node* prev;    // Pointer to the previous node in the list
        Node* next;    // Pointer to the next node in the list

        // Node constructor initializes data and optionally previous/next pointers
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val;   // Set node's data
            prev = p;     // Set previous pointer (default nullptr)
            next = n;     // Set next pointer (default nullptr)
        }
    };

    Node* head;          // Pointer to the first node in the list
    Node* tail;          // Pointer to the last node in the list

public:
    // Constructor initializes an empty list
    DoublyLinkedList(){
        head = nullptr;    // Empty list: no head
        tail = nullptr;    // Empty list: no tail
     }
    // Insert a node with value 'value' after the node at 'position' (0-based index)
    void insert_after(int value, int position) {
        if (position < 0) {    // Position must be zero or positive
            cout << "Position must be >= 0." << endl;
            return;
        }
        Node* newNode = new Node(value);    // Create new node with value
        if (!head) {                        // If list is empty, new node becomes head and tail
            head = tail = newNode;
            return;
        }
        // Traverse to node at the given position or nullptr if position too large
        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;
        if (!temp) {        // Position is beyond the current list size, insertion fail
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;    // avoid memory leak by deleting allocated node
            return;
        }
        // Link newNode in between temp and temp->next
        newNode->next = temp->next;  // New node's next is current node's next
        newNode->prev = temp;        // New node's prev is current node (temp)
        if (temp->next)              // If temp is not tail
            temp->next->prev = newNode;  // Adjust the next node's prev pointer to newNode
        else
            tail = newNode;              // If inserting at tail, update tail pointer
        temp->next = newNode;            // Link temp's next to newNode
    }
    // Delete the first node found with the given value
    void delete_val(int value) {
        if (!head) return;        // Empty list, nothing to delete
        Node* temp = head;
        // Traverse to find the node with the specified value
        while (temp && temp->data != value)
            temp = temp->next;
        if (!temp) return;      // Value not found, nothing to delete
        if (temp->prev)         // Relink pointers to remove Temp from the list
            temp->prev->next = temp->next;  // Link previous node's next to temp's next
        else
            head = temp->next;              // If deleting head, move head forward
        if (temp->next)
            temp->next->prev = temp->prev;  // Link next node's prev to temp's prev
        else
            tail = temp->prev;              // If deleting tail, move tail back
        delete temp;     // Free memory for deleted node
    }
    // Delete the node at the specified position (1-based index)
    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
        if (pos == 1) {  // If position is 1, remove head node
            pop_front();
            return;
        }
        Node* temp = head;
        for (int i = 1; i < pos; i++) {
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;     // Move temp to the desired position
        }
        if (!temp) {  // Position out of range
            cout << "Position doesn't exist." << endl;
            return;
        }
        if (!temp->next) {  // If node is tail, remove tail
            pop_back();
            return;
        }
        // Re-link neighbors to bypass temp node
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;    // Delete the node at pos
    }
    // Add a node at the end of the list
    void push_back(int v) {
        Node* newNode = new Node(v);  // Create new node with value
        if (!tail)    // If list empty, new node is head and tail
            head = tail = newNode;
        else {
            tail->next = newNode;  // Link current tail's next to newNode
            newNode->prev = tail;  // Link newNode's prev to current tail
            tail = newNode;        // Update tail pointer to newNode
        }
    }
    // Add a node at the front of the list
    void push_front(int v) {
        Node* newNode = new Node(v);  // Create new node with value
        if (!head)    // If list empty, new node is head and tail
            head = tail = newNode;
        else {
            newNode->next = head;  // New node's next is old head
            head->prev = newNode;  // Old head's prev points to newNode
            head = newNode;        // Update head to newNode
        } 
    }
    // Remove node from the front of the list
    void pop_front() {
        if (!head) {   // Empty list
            cout << "List is empty." << endl;
            return;
        }
        Node* temp = head;   // Temporarily store old head
        if (head->next) {     // More than one node
            head = head->next;   // Move head forward
            head->prev = nullptr; // Remove backward link to old head
        }
        else   // Only one node in the list
            head = tail = nullptr;   // List becomes empty
        delete temp;    // Delete old head node
    }
    // Remove node from the back of the list
    void pop_back() {
        if (!tail) {   // Empty list
            cout << "List is empty." << endl;
            return;
        }
        Node* temp = tail;    // Temporarily store old tail
        if (tail->prev) {     // More than one node
            tail = tail->prev;  // Move tail backward
            tail->next = nullptr;  // Remove forward link to old tail
        }
        else  // Only one node in the list
            head = tail = nullptr; // List becomes empty
        delete temp;  // Delete old tail node
    }
    // Destructor: cleans up all nodes to prevent memory leaks
    ~DoublyLinkedList() {
        while (head) {   // While list is not empty
            Node* temp = head;  // Temporarily hold current head
            head = head->next;  // Move head forward
            delete temp;        // Delete old head
        }
    }
    // Print list from head to tail
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {   
            cout << current->data << " "; // Output current node's data
            current = current->next;   // Move forward
        }
        cout << endl;
    }
    // Print list from tail to head (reverse order)
    void print_reverse() {
        Node* current = tail;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";  // Output current node's data
            current = current->prev;       // Move backward
        }
        cout << endl;
    }
    // New method: print every other element starting with the first
    void every_other_element(){
        Node* current = head;      // Start at head of the list
        bool printNode = true;     // To print every other node

         if (!current){
            cout << "List is empty." << endl;
            return;
         }
         cout << "Every other element: ";
         while (current){
            if (printNode){
                cout << current->data << " ";  // Print current node's data
            }
            printNode = !printNode;  // Flip toggle to skip next node
            current = current->next; // Move to next node
         }
         cout << endl;
    }
};
// Main function to demonstrate the DoublyLinkedList and new method
int main() {
    DoublyLinkedList dll;  // Create doubly linked list object

    // Add some elements to the list
    dll.push_back(10);
    dll.push_back(20);
    dll.push_back(30);
    dll.push_back(40);
    dll.push_back(50);

    cout << "Full list: ";
    dll.print();  // Output full list, should be 10 20 30 40 50

    dll.every_other_element();  // Output every other element, should print 10 30 50

    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS; // dummy statement to avoid compiler warning
    return 0;
}
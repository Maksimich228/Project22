#include <mutex>
struct Node {
    int value;
    Node* next;
    std::mutex* node_mutex;
};
class FineGrainedQueue {
    Node* head;
    std::mutex* queue_mutex;
public:
    FineGrainedQueue() : head(nullptr), queue_mutex(new std::mutex()) {}
    void insertIntoMiddle(int value, int pos) {
        Node* newNode = new Node{ value, nullptr, new std::mutex() };
        queue_mutex->lock();
        Node* current = head;
        Node* prev = nullptr;
        int currentPos = 0;
        while (current != nullptr && currentPos < pos) {
            if (prev != nullptr) {
                prev->node_mutex->unlock();
            }
            prev = current;
            current = current->next;
            currentPos++;
\            current->node_mutex->lock();
        }
        newNode->next = current;
        if (prev != nullptr) {
            prev->next = newNode;
            prev->node_mutex->unlock(); 
        }
        else {
            
            head = newNode;
        }

        if (current != nullptr) {
            current->node_mutex->unlock(); 
        }

        queue_mutex->unlock();
    }
};


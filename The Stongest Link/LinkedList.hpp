#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <stdexcept>

template<typename T>
class LinkedList
{
    private:

    // Node definition
    struct Node
    {
        Node* next;
        T data;
        Node(T d, Node* n) : data(d), next(n){}
    }* head_;

    public:

    // Constructor
    // Initializes head to null
    LinkedList() : head_(nullptr){}

    // Ruturn true if the list is empty, otherwise false
    bool empty()
    {
        //if our linked lists head is a null pointer
        if (head_ == nullptr)
        {
            //return true, because the linked list is empty
            return true;
        }
        else
        {
            //return false, because there is something in the linked list
            return false;
        }
    }

    // Return the number of nodes in the list
    size_t size()
    {
        //if the linked list is empty
        if(empty())
        {
            //return a value of 0
            return 0;
        }
        else
        {
            //counter for the number of nudes
            size_t numNodes = 0;

            //an iteration for each node
            Node* iter = head_;

            //while our current node is not a null pointer
            while(iter != nullptr)
            {
                //increase the number of nodes by 1
                numNodes++;

                //set the iteration equal to the next node in the linked list
                iter = iter->next;
            }

            //return the number of nodes
            return numNodes;
        }
    }

    // Create a new node to contain value and insert
    // the node to the front of the list
    void pushFront(T value)
    {
        //create a new node with the passed in value and set the next node to the current head node
        Node* newNode = new Node(value, head_);

        //set the head to the new node
        head_ = newNode;
    }

    // Create a new node to conatin value and insert
    // the node to the back of the list
    void pushBack(T value)
    {
        //create a new node with the passed in value and set the next node to a nullpointer (because it is at the end of thelinked list)
        Node* newNode = new Node(value, nullptr);

        //if head is a null pointer
        if(head_ == nullptr)
        {
            //set the new node to the head node
            head_ = newNode;
        }
        else
        {
            //an iteration for each node
            Node* iter = head_;

            //while our current node is not a null pointer
            while(iter != nullptr)
            {
                //if the next node is a null pointer (signifying the end of the linked list)
                if(iter->next == nullptr)
                {
                    //set that node equal to the new node
                    iter->next = newNode;
                    break;
                }

                //set the iteration equal to the next node in the linked list
                iter = iter->next;
            }
        }
    }

    // Retrieve the node value at the specified list index.
    // Note: Your implementation may assume that the value
    // passed into the index parameter is within the range
    // of the linked list size
    T at(size_t index)
    {
        if(index >= size())
        {
            throw std::out_of_range("Index is out of range");
        }

        //an iteration for each node
        Node* iter = head_;

        //get to the index location in the linked list
        for (size_t i = 0; i < index; i++)
        {
            //set the iteration equal to the next node in the linked list
            iter = iter->next;
        }

        //return the data
        return iter->data;
    }

    // Remove the head node in the list such that
    // the second node in the list should become
    // the new head node. Then return the previous
    // head node's value.
    // Note: Your implementation may assume that the
    // size of the linked list is greater than zero
    T popFront()
    {
        //exception handling for empty list
        if(empty())
        {
            //throw a logic error
            throw std::logic_error("List is empty");
        }

        //store the data value of the head node
        T prevHeadVal = head_->data;

        //store the next node after the head node so we may reference it to set the new head node
        Node* nextHead = head_->next;

        //delete the current head node
        delete head_;

        //set the head node to the next node that we stored previously
        head_ = nextHead;

        //return the original head node's value
        return prevHeadVal;
    }

    // Remove the node at the specified list index.
    // Return true if the node at the specified index
    // could be removed, otherwise false
    bool removeAt(size_t index)
    {
        //the index in the linked list
        size_t listIndex = 0;

        //an iteration for each node
        Node* iter = head_;

        //the previous node in the linked list
        Node* prevNode;

        //0 case
        if(index == 0)
        {
            //set the head node to the second node in the linked list
            head_ = iter->next;

            //delete the original head node
            delete iter;
            return true;
        }

        //loop through the linked list indexes until reaching the passed in index
        for (size_t i = 0; i < index; i++)
        {
            //if we are at the node before the desired node
            if (i == index-1)
            {
                //store that node into prevNode for future use
                prevNode = iter;
            }

            //set the iteration equal to the next node in the linked list
            iter = iter->next;

            //if we reached the end of the linked list
            if(iter == nullptr)
            {
                return false;
            }
        }

        //set the previous node's next node to the desired node's next node
        prevNode->next = iter->next;

        //delete the desired node
        delete iter;
        return true;
    }

    // Remove all nodes in the list
    void clear()
    {
        //while the linked list is not empty
        while(!empty())
        {
            //remove the first element in the list
            popFront();
        }
    }

    // Destructor
    // Remove any remaining nodes in the list
    ~LinkedList()
    {
        //clear the linked list by calling the clear member function
        clear();
    }

    //Definition of iterator data type
    //for iterating through a linked list
    class Iterator
    {
        private:
        Node* current_;

        public:

        Iterator(Node* head) : current_(head){}

        //Get address of current node's data
        T* current()
        {
            if(current_ == nullptr)
            {
                return nullptr;
            }

            return &current_->data;
        }

        //Move to the next node
        void next()
        {
            if(current_ != nullptr)
            {
                current_ = current_->next;
            }
        }

        //Return true if there is a next node, otherwise false
        bool hasNext()
        {
            return current_ != nullptr;
        }
    };

    //Return a new iterator object
    Iterator generateIterator()
    {
        return Iterator(head_);
    }
};

#endif
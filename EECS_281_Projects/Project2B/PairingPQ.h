// Project identifier: 0E04A31E0D60C01986ACB20081C9D8722A1899B6

#ifndef PAIRINGPQ_H
#define PAIRINGPQ_H

#include "Eecs281PQ.h"
#include <deque>
#include <utility>

// A specialized version of the priority queue ADT implemented as a pairing heap.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class PairingPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Each node within the pairing heap
    class Node {
        public:
            // TODO: After you add add one extra pointer (see below), be sure to
            // initialize it here.
            explicit Node(const TYPE &val)
                : elt{ val }, child{ nullptr }, sibling{ nullptr }, parent{nullptr}
            {}

            // Description: Allows access to the element at that Node's position.
			// There are two versions, getElt() and a dereference operator, use
			// whichever one seems more natural to you.
            // Runtime: O(1) - this has been provided for you.
            const TYPE &getElt() const { return elt; }
            const TYPE &operator*() const { return elt; }

            // The following line allows you to access any private data members of this
            // Node class from within the PairingPQ class. (ie: myNode.elt is a legal
            // statement in PairingPQ's add_node() function).
            friend PairingPQ;

        private:
            TYPE elt;
            Node *child;
            Node *sibling;
            // TODO: Add one extra pointer (parent or previous) as desired.
            Node *parent;
    }; // Node


    // Description: Construct an empty pairing heap with an optional comparison functor.
    // Runtime: O(1)
    explicit PairingPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp }, root {nullptr}, count{0} {
        // TODO: Implement this function.
        //nothing else needed since it do be empty
    } // PairingPQ()


    // Description: Construct a pairing heap out of an iterator range with an optional
    //              comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    // TODO: when you implement this function, uncomment the parameter names.
    template<typename InputIterator>
    PairingPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp }, root {nullptr}, count {0} {
        // TODO: Implement this function.
        while(start != end){
            push(*start);
            start++;
        }
    } // PairingPQ()


    // Description: Copy constructor.
    // Runtime: O(n)
    PairingPQ(const PairingPQ &other) :
        BaseClass{ other.compare }, root{nullptr}, count {0} {
        // TODO: Implement this function.
        // NOTE: The structure does not have to be identical to the original,
        //       but it must still be a valid pairing heap.
        std::deque<Node*> pqnodes;
        pqnodes.push_back(other.root);
        Node *curr = other.root;
        while(!pqnodes.empty()) {
            curr = pqnodes.front(); 
            if(curr->sibling != nullptr) {
                pqnodes.push_back(curr->sibling);
            }
            if(curr->child != nullptr) {
                pqnodes.push_back(curr->child);
            }
            push(curr->getElt());
            pqnodes.pop_front();
            
        }
    } // PairingPQ()


    // Description: Copy assignment operator.
    // Runtime: O(n)
    // TODO: when you implement this function, uncomment the parameter names.
    PairingPQ &operator=(const PairingPQ &rhs) {
        // TODO: Implement this function.
        // HINT: Use the copy-swap method from the "Arrays and Containers" lecture.
        PairingPQ temp(rhs);

        std::swap(count, temp.count);
        std::swap(root, temp.root);
        return *this;
    } // operator=()


    // Description: Destructor
    // Runtime: O(n)
    ~PairingPQ() {
        // TODO: Implement this function.
        if(!empty()) {
            std::deque <Node*> nodes;
            Node *curr = root;
            nodes.push_back(root);
            while(!nodes.empty()) {
                curr = nodes.front();
                if(curr->child != nullptr) {
                    nodes.push_back(curr->child);
                }
                if(curr->sibling != nullptr) {
                    nodes.push_back(curr->sibling);
                }
                delete nodes.front();
                nodes.pop_front();
                
            }
        }
    } // ~PairingPQ()


    // Description: Assumes that all elements inside the pairing heap are out of order and
    //              'rebuilds' the pairing heap by fixing the pairing heap invariant.
    //              You CANNOT delete 'old' nodes and create new ones!
    // Runtime: O(n)
    virtual void updatePriorities() {
        // TODO: Implement this function.
        std::deque<Node*> nodes;
        nodes.push_back(root);
        Node *curr;
        while(!nodes.empty()) {
            curr = nodes.front();
            nodes.pop_front();
            if(curr->sibling != nullptr) {
                nodes.push_back(curr->sibling);
            }
            if(curr->child != nullptr) {
                nodes.push_back(curr->child);
            }
            curr->parent = nullptr;
            curr->child = nullptr;
            curr->sibling = nullptr;
            root = meld(curr, root);
        }
    } // updatePriorities()


    // Description: Add a new element to the pairing heap. This is already done.
    //              You should implement push functionality entirely in the addNode()
    //              function, and this function calls addNode().
    // Runtime: O(1)
    virtual void push(const TYPE &val) {
        addNode(val);
    } // push()


    // Description: Remove the most extreme (defined by 'compare') element from
    //              the pairing heap.
    // Note: We will not run tests on your code that would require it to pop an
    // element when the pairing heap is empty. Though you are welcome to if you are
    // familiar with them, you do not need to use exceptions in this project.
    // Runtime: Amortized O(log(n))
    virtual void pop() {
        std::deque<Node*> nodes;
        if(root->child == nullptr) {
            delete root; // no child
            count--;
            return;
        }
        Node *children = root->child;
        if(children->sibling == nullptr) { // only child
            delete root;
            root = children;
            
        }
        else {
            while(children != nullptr) {
                nodes.push_back(children);
                children = children->sibling;
            }
            Node *first;
            Node *second;
            while(nodes.size() > 1) {
                first = nodes.front();
                nodes.pop_front();
                second = nodes.front();
                nodes.pop_front();
                first->parent = nullptr;
                first->sibling = nullptr;
                second->parent = nullptr;
                second->sibling = nullptr;

                nodes.push_back(meld(first, second));
            }
            delete root;
            root = nodes.back();
            
        }
        count--;
    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of the
    //              pairing heap.  This should be a reference for speed.  It MUST
    //              be const because we cannot allow it to be modified, as that
    //              might make it no longer be the most extreme element.
    // Runtime: O(1)
    virtual const TYPE &top() const {
        // TODO: Implement this function

        // These lines are present only so that this provided file compiles.
         // TODO: Delete this line
        
        return root->getElt();      // TODO: Delete or change this line
    } // top()


    // Description: Get the number of elements in the pairing heap.
    // Runtime: O(1)
    virtual std::size_t size() const {
        // TODO: Implement this function
        return count; // TODO: Delete or change this line
    } // size()

    // Description: Return true if the pairing heap is empty.
    // Runtime: O(1)
    virtual bool empty() const {
        // TODO: Implement this function
        return (count == 0); // TODO: Delete or change this line
    } // empty()


    // Description: Updates the priority of an element already in the pairing heap by
    //              replacing the element refered to by the Node with new_value.
    //              Must maintain pairing heap invariants.
    //
    // PRECONDITION: The new priority, given by 'new_value' must be more extreme
    //               (as defined by comp) than the old priority.
    //
    // Runtime: As discussed in reading material.
    // TODO: when you implement this function, uncomment the parameter names.
    void updateElt(Node* node, const TYPE &new_value) {
        // TODO: Implement this function
        node->elt = new_value;
        if(node != root) { //has parent
           if(this->compare(node->parent->getElt(), node->getElt())) { // parent < updated element
                Node *par = node->parent;
                if(par->child == node) { //left
                    if(node->sibling == nullptr) { // sibling
                        par->child = nullptr;
                        node->parent = nullptr;
                    }
                    else{
                        par->child = node->sibling;
                        node->parent = nullptr;
                        node->sibling = nullptr;
                    }
                }
                else { //not leftmost
                    Node *sibling = par->child;
                    while(sibling->sibling != node) {
                        sibling = sibling->sibling;
                    }
                    if(node->sibling == nullptr) {
                        sibling->sibling = nullptr;
                        node->parent = nullptr;
                    }
                    else {
                        sibling->sibling = node->sibling;
                        node->parent = nullptr;
                        node->sibling = nullptr;
                    }
                }
           root = meld(node, root);
           }
        }
    } // updateElt()


    // Description: Add a new element to the pairing heap. Returns a Node* corresponding
    //              to the newly added element.
    // Runtime: O(1)
    // TODO: when you implement this function, uncomment the parameter names.
    // NOTE: Whenever you create a node, and thus return a Node *, you must be sure to
    //       never move or copy/delete that node in the future, until it is eliminated
    //       by the user calling pop().  Remember this when you implement updateElt() and
    //       updatePriorities().
    Node* addNode(const TYPE &val) {
        // TODO: Implement this function
        Node *add = new Node(val);
        if(empty()) {
            root = add;
            count++;
            return add;
        }
        else {
            root = meld(add, root);
            count++;
            return add;
        }
    } // addNode()


private:
    // TODO: Add any additional member variables or member functions you require here.
    // TODO: We recommend creating a 'meld' function (see the Pairing Heap papers).

    Node* meld(Node *a, Node *b) {
        //check nullptr, may not be necessary
        if(a == nullptr) {
            if(b == nullptr) {
                return nullptr;
            }
            return b;
        }
        if(b == nullptr) {
            return a;
        }
        //check if same
        if (a == b) {
            return b;
        }
        else if (this->compare(a->getElt(), b->getElt())) { //a < b, b becomes root
            a->parent = b;
            a->sibling = b->child;
            b->child = a;
            return b;
        }
        else { // a > b
            b->parent = a;
            b->sibling = a->child;
            a->child = b;
            return a;
        }
    }

    // NOTE: For member variables, you are only allowed to add a "root pointer"
    //       and a "count" of the number of nodes.  Anything else (such as a deque)
    //       should be declared inside of member functions as needed.
    Node *root;
    size_t count;
};


#endif // PAIRINGPQ_H

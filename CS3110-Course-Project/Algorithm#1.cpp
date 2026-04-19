/*All comments are typed from me - Iffat Rahman

Reminders:

Keep in mind that it's nearly impossible/rare to create an original unque algorithm from the ground up as most or all 
algorithms are evolutions, adaptions, derivations of exsisting algroithms with their own twist based on the problem 
said algorithm is solving. The twist itsell doesnt have to be exlusive or extreme, it can be as simple as creating 
a difference in how you traverse a list etc. 
Rather, the focus of this assignment is to: 

For this project, we will create two algorithms that are different in regards to the following. This file is Algorithm#1: 
 - Order of growth 
 -  Number of basic operations executed
 - What strategy this algorithm follows or is derived by 

Algorithm#1 below follows this strategy and the inspiration behind the algorithm derived by said : Transform and Conquer - Heapsort
Rather than reducing the given problem into a single smaller instance of the orignal problem or several subproblems and then combining the
solution of said sub problems to solve the original problem, we do a two stage process: Transform the problem intoa different form and then 
we conquer the original problem by solving the altered problem

*/


#include <iostream> //for basic I/O
#include <fstream> //for basic/fundemtnal (MUST) of creating, writing, and reading files. 
#include <sstream> //for istringstream object  to use iss(value) method from said object to read a specific word from a line within in a fil. This relies on getline(x,y) so it can break the word down within the line.
#include <vector> //to use vectors
#include <string> //so I can use certain built in methods for strings like getting the size
using namespace std;

//heaps are follow the array convention. Thus, implementing it as a linked list means that we should implement it where there are left and right child pointers

//recall that linked lists are a type of list where the elements are known as a collection of nodes that are essentially pointers known as a link.
//therefor, when creating a node, you create a pointer to a struct. If you want to access a data member of said instance you must use the member access operator (->) instead of the dot operator (.) as you would with a normal instance. This is because we are working with pointers and not the actual instance itself.

struct CreateNode{  //this struct is used as a simple linked list to store our input data for simple traversal. We dont immediately create a heap node for each input data, just a simple node for it instead. again for simple traversal so that when we need to manipulate from it, its easier

    //data members
    int Value; //data value of each node
    CreateNode* LinkNext; //stores the memory address of the next node, pointer usage

     //constructor
     CreateNode(int Val){
        Value = Val;
        LinkNext = NULL; 
     }
    
};

struct ModifyPlacementNode{ //this heap is used for stage 2 and to allow us to make it possible to traverse a heap from left right etc
/*

this struct looks at every node form the linked list of nodes within CreateNode and creeates a heap node for each node from said linked list. 
You might ask, what is a heap node? A heap node must have the following three links: left, right, and parent. This is because a heap is a complete binary tree and thus every node can have up to two children and one parent.

*/
    //data members
    int Value;
    ModifyPlacementNode* LeftLink; //assuming currnode has a sibling
    ModifyPlacementNode* RightLink; //assuming currnode has a sibling
    ModifyPlacementNode* Parent;

    //constructor
    ModifyPlacementNode(int Val){
        int Value = Val;
        LeftLink = NULL;
        RightLink = NULL;
        Parent = NULL;
    }

};

void AddToLinkedList(CreateNode*& Head, int Val); //this method is used to add a node to a linked list by using the tools from the first struct

vector<ModifyPlacementNode*> HeapTreeFromLinkedList(CreateNode* Head); //This method essentially executes the second struct to create a heap node for each node from the linked list of the struct creadnode, thus creating a binary tree and not a heap tree. This is due to the method not calling heapfiy

void Heapify(vector<ModifyPlacementNode*>& Nodes, int n, int i); //this method is to do the heapify procedure for both stage 1 and stage 2.

void FinalizeHeapTree(vector<ModifyPlacementNode*>& Nodes); //this method builds upon the HeapTreeFromLinkedList method to ultimately transition the binary tree of heap nodes to a full on heap tree via heapify. After this method is done, you will have a heap tree of heap nodes.

//stage 2: Swap root node with the last node of the tree. Take root node out for sort. Heapify tree. Continue until there are no nodes left in the tree. The last node to stay is the root node
CreateNode* SwapRootWithLastNode(vector<ModifyPlacementNode*>& Nodes, int n);

CreateNode* HeapSort(CreateNode* Input); //THIS DOES THE ACTUAL SORTING FOR STAGE 2




int main(){
   

}

void AddToLinkedList(CreateNode*& head, int Val){ //this method is used to add a node to a linked list by using the tools from the first struct only. 
    CreateNode* NewNode = new CreateNode(Val); //create a node by creating a pointer to the struct and invoke the paramterized constructor by passing respective argument

    if(head==NULL){ //if head node doesnt exsist
        head = NewNode;
        return; //method ends
    }

    CreateNode* CurrNode = head;  //now both nodes point are the same details
    while(CurrNode->LinkNext!=NULL){ //currnode access it's link (memroy address of the node we point to)
        CurrNode = CurrNode->LinkNext; //currnode is now initalized to the next node
    }
    //the moment we leave the while loop, currnode is now at the very last node. 
    CurrNode->LinkNext = NewNode; //the moment were at the tail of the linked list (which is when the last node has a null link) we can modify the link of it to point to the new node we created. This new node is the lastest/last node of the linked list

}


vector<ModifyPlacementNode*> HeapTreeFromLinkedList(CreateNode* Head){ //as the name suggests

    //create vector where the elements are pointers to the instances of the struct ModifyPlacementNode, which are essentially nodes from said linked list
    vector<ModifyPlacementNode*> Nodes;

    //we create one heap node for every node from the linked list. So the linked list is what is intialized first for each inputted data?
    CreateNode* CurrentNode = Head;
    while(CurrentNode!=NULL){
        Nodes.push_back(new ModifyPlacementNode(CurrentNode->Value));// we create a node under the struct ModifyPlacementNode
        CurrentNode = CurrentNode->LinkNext; //CurrentNode moves on to the next node in the linked list thanks to the link
    }

    //A heap node for node from the linked list means we need to intialize the link for left, right, and it's parent as it's apart of the complete binary tree and needed for traversing
    for(int i = 0; i<(int)Nodes.size(); i++){

        //accomdate for index couting:
        int LeftIndex = 2 * i + 1;
        int RightIndex = 2 * i + 2;

        if(LeftIndex < (int)Nodes.size()){
            Nodes[i]->LeftLink = Nodes[LeftIndex]; //in the vector of nodes for ModifyPlacementNode, go to the current element (or Node) initalize the memory address of the left link to the link of the element (Node) that has index of left link
            Nodes[LeftIndex]->Parent = Nodes[i];
        }

        if(RightIndex < (int)Nodes.size()){
            Nodes[i]->RightLink = Nodes[RightIndex]; //in the vector of nodes for ModifyPlacementNode, go to the current element (or node) intitalze the memory address of the right link to the link of the element (Node) that has the index of right link
            Nodes[RightIndex]->Parent = Nodes[i];
        }
    }

    return Nodes;

}

void Heapify(vector<ModifyPlacementNode*>& Nodes, int n, int i){ //this method is used to heapify the tree by ensuring that the definition of a heap is followed. This is used in both stage 1 and stage 2
    int largest = i;
    int LeftIndex = 2 * i + 1;
    int RightIndex = 2 * i + 2;

    if(LeftIndex < n && Nodes[LeftIndex]->Value > Nodes[largest]->Value){
        largest = LeftIndex;
    }

    if(RightIndex < n && Nodes[RightIndex]->Value > Nodes[largest]->Value){
        largest = RightIndex;
    }

    if(largest != i){
        swap(Nodes[i]->Value, Nodes[largest]->Value); //swap the value of the current node with the value of the largest node

        Heapify(Nodes, n, largest); //recursively heapify the affected subtree
    }

} 

void FinalizeHeapTree(vector<ModifyPlacementNode*>& Nodes){ //this method builds upon the HeapTreeFromLinkedList method to ultimately transition the binary tree of heap nodes to a full on heap tree via heapify

    int n = Nodes.size();

    int LastParentNodeIndex = (n / 2) - 1; //the last parent node is the node that has the last child node, thus we can use the array convention to find the index of the last parent node by using this formula

    for(int i = LastParentNodeIndex; i >= 0; i--){ //we start from the last parent node and work our way up to the root node, thus we decrement the index of the parent node as we go up
        Heapify(Nodes, n, i);    

    }
} 

//stage 2: Swap root node with the last node of the tree. Take root node out for sort. Heapify tree. Continue until there are no nodes left in the tree. The last node to stay is the root node
CreateNode* SwapRootWithLastNode(vector<ModifyPlacementNode*>& Nodes, int n){

    CreateNode* SortedArray = nullptr; //remember, when we create a pointer to a struct were essentially, creating a node. The node here will be used to create a list of sorted nodes

    for(int Size = n; Size>1; Size--){

        //swap the values between the root node and the last node, remember Size is the variable that represents the total number of nodes in the linked list of heap nodes, thus we -1 to get the last heap node to account for index counting
        swap(Nodes[0]->Value, Nodes[Size-1]->Value); 

        CreateNode* Taken = new CreateNode(Nodes[Size-1]->Value); //we take the value of the last node now that it contains the value of the previous root node, which is the largest value in the heap tree, to ultimately create our sorted list
        Taken->LinkNext = SortedArray;
        SortedArray = Taken; 

        //heapify the tree because its not following regular heap structure
        Heapify(Nodes, Size-1, 0);
    }

    CreateNode* Last = new CreateNode(Nodes[0]->Value);
    Last->LinkNext = SortedArray;
    SortedArray = Last;
    return SortedArray;
} 

CreateNode* HeapSort(CreateNode* Input){ //THIS DOES THE ACTUAL SORTING FOR STAGE 2

    vector<ModifyPlacementNode*>Nodes = HeapTreeFromLinkedList(Input); 

    FinalizeHeapTree(Nodes);

    CreateNode* SortedArray = SwapRootWithLastNode(Nodes, Nodes.size());

    for(ModifyPlacementNode* Node : Nodes){
        delete Node;
    }

    return SortedArray;
}




/*

Other notes about how this algorithm was implemented: 

Heapsort is a Tranform and Conquer technqiue as it follows this two stage technique
- stage 1 Transform: Construct a heap for the raw unsorted given input text file via the bottom up approach
during this process sorting should and will be irrelevant. Reminder, a heap is a complete binary tree 
where every parent node is >= to it's children, this is the def & property of a heap. 
Thus, the largest verticie sits as the root node But how do we transform the given input and construct it into a heap?: We do so via a heapify process
1. Place every vertex in the tree in the given order
2. Start from the last parental node and make sure the def of the heap is followed, otherwise swap
the vertex with it's largest child node and continue downaward until you no longer can. 
3. Now do this with the previous parent node and the way till you've worked towards the root node.
The process heapify is used above to construct the heap from the given input. Overall, heapify is an algorithm or a precedure to ensure that a tree remains as a heap tree

keep in mind that we need to construct the heap into a link-list structre as the output of this problem requires the 
the output of this problem requires it to be an adjancey list which is an array of a linked lists. 

- stage 2 Concquer: The process heapify used here is to ensure that the heap property is still followed for every time we take the previous root node out of the heap to output sorted data.
In stage 2, we take the input that was transformed into a heap from stage 1 and finally begin to sort the heap by swapping the root node
with the last element in the current form of the heap and then take the previous root node out of the heap. As a result,
the heap may loose it's heap structure so we then heapify the tree to ensure that definition of a heap tree is still present. Remember,
by the end of stage 1, while the nodes are placed in a way where the parent node is greater than it's child or children if any. 


*/
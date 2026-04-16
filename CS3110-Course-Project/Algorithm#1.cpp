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

int main(){
    int x;
}

/*

Other notes about how this algorithm was implemented: 

Heapsort is a Tranform and Conquer technqiue as it follows this two stage technique
- stage 1: Construct a heap for the given input text file via the bottom up approach
, but how?: Reminder a heap is a complete binary tree where every parent node is >= to 
it's children. Again the goal is to construct a heap not to sort the possibly unsorted 
input. 


*/
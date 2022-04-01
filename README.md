This is a brute-force algorithm for the Knight's Tour written in C++. 

This is a project assignment for my Discrete Mathematics course in which we were tasked with individually exploring one of a myraid of different problems 
in discrete mathematics. I thought the knight's tour, being a hamiltonian path type problem was interesting so I decided to delve into that.

While a brute-force algorithm is the least efficient way to solve this problem (there are a few other algorithms which give priority to certain moves), I 
found it to be much more interesting. The algorithm is written to abstract away all of the implementation, leaving a very simple sub-30 line main file. 
I decided to write a solver which is dynamically sized at runtime, so I could write one algorithm and test it was various sizes. This meant array-based 
solutions were not possible as they are statically sized at compile-time. I decided it would be an interesting to represent a two-dimensional board using a 
standrd 1-D vector and perform algorithmic bound-checking.

In this initial commit, the algorithm results in a stack overflow because the recursion is implemented poorly. Because it's a brute-force algorithm, the 
call stack gets out of hand rather quickly. This will be fixed in a later push, 

This was a homework assignment assigned in my data structures class. It is written in C++ using a custom virtual machine in Docker that was made for the class. I used Visual Studio when writing my code.

<h2>Startup Merging Tracker</h2>
- The code written for this portion of the assignment can be found in the 'company' directory under the company.cpp and company.hpp files.
- Startups these days are merging so fast, it’s hard to keep track of who is in what company. Company A merges with Company B, and Company C merges with Company D, and then the two merged companies merge, and suddenly, employees from companies A and C find themselves being colleagues. As this gets sufficiently more difficult to follow, the assignment was to write a class that can be a tracker of these mergin startups.
- Here is how this works: Initially, each starts a startup company by himself/herself. Then, companies may merge. When you have a merge command, you will be given the numbers of two representative students, one from each company. Then, for each of those two students, you find the “biggest” company they are in, i.e., companies that are not subcompanies of any bigger company; let’s call them A and B. Those two companies A and B are then merged into a new company; let’s call it C. C will become the parent company of A and B.
- Sometimes, companies also split up again. When we call split, we will again give you a representative student. Then, you find the biggest company that the student is in—let’s call it A. As a result of the split, A should be completely removed, and the two companies that were at some point in the past merged to become A will now be individual companies without a parent again. If the student is only in their own 1-person company, split does nothing.
- For the assignment, I built a data structure that allows the easy processing of sequences of merges and splits, and answers queries about whether student A and B are in the same company.
- To illustrate this, consider the following example with 5 students. After each command, we are showing you the structure of the nested companies with braces. The notation { {1}, { {2}, {3} } } means that we have a company with two subcompanies: the first subcompany is just student 1, while the second subcompany again has two subcompanies, one consisting of just student 2, the other consisting of just student 3.

merge (0,1)   => { {0}, {1} }, {2}, {3}, {4}
merge (2,3)   => { {0}, {1} }, { {2}, {3} }, {4}
merge (0,3)   => { { {0}, {1} }, { {2}, {3} } }, {4}
split (2)     => { {0}, {1} }, { {2},{3} }, {4}
split (2)     => { {0}, {1} }, {2}, {3}, {4}
merge (2,4)   => { {0}, {1} }, { {2}, {4} }, {3}
split (0)     => {0}, {1}, { {2}, {4} }, {3}

<h2>Permutations of String (Recursion)</h2>
- This simple program takes an input string and outputs all permutations of its letters. For example, if the input is USC, then the output (in any order) would be USC, UCS, SUC, SCU, CUS, CSU.

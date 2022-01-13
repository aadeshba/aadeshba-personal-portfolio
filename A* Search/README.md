Written in C++ in Visual Studio.
## Backtracking Program
This program solves a version of the subset sum problem.
* Some classes are a lot of work, and at the end, you have very little actual knowledge to show for. Others are the other way around. Some are neither work nor useful, and in some you work really hard and hopefully learn a lot. This program figures out which combination of classes causes you to learn the most, without exceeding your workload capacity.
* This program takes just one command line parameter, the name of the input file. The input file will have two numbers on the first line: n is the total number of classes from which you can choose, and the second number W is a double, capturing the total amount of work you can do for the semester. Next come n lines, each describing a class. The class i is described by first the class name s(i) (a string that does not contain any white space), followed by one or more whitespaces. Next come two non-negative doubles w(i) and L(i). The first of these is the amount of total work you need to do for class i, and the second is the total amount you learn from class i. Here is an example of what this may look like:
* The program will output the maximum total amount you can learn from any combination of classes whose total work does not exceed W. In the example above, the correct output would be 10.36, by combining CSCI104 with ENGR102. You cannot combine CSCI104 with any of the other classes (it would exceed your workload capacity), and you don't learn as much if you take CSCI170 with CSCI280; also, CSCI170 and ENGR102 and CSCI280 together exceed your workload capacity.
* Simply typing make learning will create an executable to run the program called "learning" in this directory.
## D-ary Heap
In order to aid with the next part of my project (solving the word transformation game "doublet" using A* search), I wrote a d-ary heap class which can be found in heap.h. This class can be used to create a MinHeap where each node has the specified number of children d. 
## A* Search
This program compiles with 'make doublet' and creates an executable called 'doublet' which takes starting word, ending word, and then input dictionary file as command line parameters. The input dictionary file is a list of valid words that can be used in the transofrmation.
### The problem being solved:
* The word game "Doublet" was invented by Lewis Carroll, and is a word transformation puzzle. Two words of identical length are given. The objective is to transform the first word into the second word by forming successive words of the same length, changing only one letter at a time. The challenge is to do the transformation in the least number of words. Here is an example from HEAD to TAIL:
```text
HEAD
HEAL
TEAL
TELL
TALL
TAIL
```
* The first row of the input dictinoary file contains a number n, indicating the number of words in the file. There will be n more rows, each with a single word, each possibly followed by some whitespace. There may be blank lines at the end of the file. The word file will not contain duplicates, and the start and end word will always be in the word file. But, there may sometimes be no way to get from the starting word to the ending word.
* The output of the program is the number of steps that can be taken to get from start to end, followed by the number of expansions (number of different words checked by the program when performing A* search).
### How I solved the problem:
* My program solves this problem by essentially creating a heuristic to determine how far each possible word is from the end result word. This is done by determining how many different letters don't match between the two. For example, HEAL and TAIL are 3 apart because only the L matches.
* Every word is given a priority based on a heuristic and a graph is created with words that can be transformed between each other (i.e. these words only have a one letter difference). Performing A* search on this graph leads to a viable (or lack thereof) series of transformations to get from the start to end word.
### Example of execution:
Starting from AAAAA, ending at BBBBB, with the following dictionary:
```text
AAAAA
AAAAB
AAABB
AABAA
AABBA
AABBB
ABBBA
BAAAA
BBBBA
BBBBB
```

1.  Expanding  `AAAAA`, we would add  `AAAAB`,  `AABAA`, and  `BAAAA`  to the heap.
2.  Expanding  `AAAAB`  (because it comes first according to operator<), we would add  `AAABB`.
3.  Expanding  `AAABB`, we would add  `AABBB`.
4.  Expanding  `AABBB`  (because it has the smaller h-value), we would add  `AABBA`.
5.  Expanding  `AABAA`  (because it has the smaller f-value), we would update  `AABBA`.
6.  Expanding  `AABBA`, we would add  `ABBBA`.
7.  Expanding  `ABBBA`, we would add  `BBBBA`.
8.  Expanding  `BBBBA`, we would add  `BBBBB`.
9.  `BBBBB`  would be the next expansion, so we're done with a total of 8 expansions (we never searched  `BAAAA`).

It would output:

```text
5
8
```

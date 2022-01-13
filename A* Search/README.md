Written in C++ in Visual Studio.
## D-ary Heap
In order to aid with the next part of my project (solving the word transformation game "doublet" by Lewis Carroll using A* search), I wrote a d-ary heap class which can be found in Minheap.h. This class can be used to create a MinHeap where each node has the specified number of children d (rather than just a binary heap). 
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

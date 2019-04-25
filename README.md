# rainbow-table
This repository is to host and possibly share the code of an implementation for a simplified rainbow table, which is the final project for my CSCI2100 course.

**WARNING FOR MY FELLOW CSCI2100 CLASSMATES:** All commits here are GPG signed with exact time that they are submitted. Do not ever copy code from here or you have to take your responsibility for plagiarism.
Also the code is not guaranteed to be correct or follow the best practices.

## Requirements
- CMAKE >= 3.14
- OpenSSL library
- C compiler that **supports pthread** (Or remove all threads-related code if you have a single-core CPU)

## File Structure
`trie.c, trie.h`: a simple modified implementation of trie to allow storage of rainbow chains.

`random.c, random.h`: random string generator

`tinymt/*`: tinyMT random number generator (since rand() has limited randomness and uncertain RAND_MAX)

`related/*`: related research papers
   
## Future Plan
If I survive the finals and have extra time, maybe I will try to implement this with CUDA.

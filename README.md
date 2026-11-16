# CS415_Project3

## Student Info

Names: Jamie Yah-Parez, Jose Gallegos <br>
Github Link: https://github.com/JaimeYahPerez/CS415_Project3 <br>

## Collaboration and Resources

jaime: https://chatgpt.com/share/e/6afaac88-1a78-83e8-bc25-d5c497c0a554 <br>

This time around I focused on psuedocode and expectations for the designs of trie data structures. Essentially to guide class design for the requirements. <br>
I wanted to know what should be achieved in time complexity for an indepth analysis. Referrals were also made to the csusfca website to understand the tst tree <br>

Jose: I worked on both the insert, search and autocomplete functions with stdtrie and bsttrie cpp files from the header file set-up from Jamie. Additionally, I helped modify functions in our main so that we'd be able to run our various and final verisons of the code.

Using the explanations and assist using Jamie's prompts for setting up our code, I used the following websites to further understand the two data structures we were working to build and learning how to use double pointers properly: <br>
https://cppreference.com/ <br>
https://www.geeksforgeeks.org/dsa/trie-insert-and-search/ <br>
https://www.geeksforgeeks.org/dsa/ternary-search-tree/

Within searching up material regarding the project using Google Search, there was some info used that was generated with Google's AI search tools. Any generted responses used were towards further assiance in visualizing the tries and verifying why certain time and space complexities make sense for the given structures.

## Testing
all files should be on the same level. warnings will appear due to a comparison with an int and size_t but will not cause issues for the ranges of our test files <br>

run as <br>
make clean <br>
make <br>
./a.out <input_file>.txt <flag 1 or 2> <br>
example: ./a.out test.txt 2 <br>
for case 1 inputs, enter queries as whole strings with no spaces <br>

# C++ Binary Tree

An implementation of a binary tree used to sort numbers and then create a sorted stack of these random numbers.

This project was more geared toward familiarizing myself with Microsoft Visual Studio and its useful features and c++ unit testing. The folder here includes a .sln solution file. Actual C++ source files can be found in the binaryTreeSort folder in this directory.

## Usage
Included in this repo is also a main release executable that, given an input specification, will generate random numbers to create a tree and then output all the numbers to 3 files defined by the input. The command format for windows powershell is:
./binaryTreeSort.exe \<random numbers file\> \<greatest to least file\> \<least to greatest file\> \<number of random numbers\>

So a full entry line will look something like:  

(directory)\dpgWinter18-19\binaryTreeSort\Release>  ./binaryTreeSort.exe './Release/<b>Results/randomNumFile.txt</b>' './Release/<b>Results/gtl.txt</b>' './Release/<b>Results/ltg.txt</b>' 100  

this will generate 100 random numbers and save the results to the bolded files in the subfolder of Release called "Results"

## Notes

I really enjoyed this project working in C++. In this past semester I had two classes that required me to program in C whereas previously I had done C++, so returning to the more modern and fully featured language was refreshing. The similarities between the two languages is also quite useful as I now know and appreciate some of the lower level specifics of C++ that derive from C such as memory management through pointers. I could easily convert the base data structure binary tree for use in C.  
The main focus for me through this projecy however, was learning how to use VS2017's more advanced features such as unit testing and team management (specifically github integration). Unit testing was particularly useful in that previously testing was done through using a main function that I could change to test all the functionality, but through VS unit testing, I can easily create and observe multiple tests all at once so I can be sure functionality is maintained through modifications of the program easily. I have no doubt that unit testing is how some of my professors have tested and graded my code before, and so knowing how to do this myself is valuable knowledge to have. Team management through the effictive use of github was also important, but since I was working alone I couldn't really utilize all the features of github. So instead I simply made a seperate branch for this project and merched it with master at completion. I'm pretty proficient at git and I have worked with teams through github before, but you can never have enough practice.

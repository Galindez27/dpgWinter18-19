# C++ Binary Tree

An implementation of a binary tree used to sort numbers and then create a sorted stack of these random numbers.

This project was more geared toward familiarizing myself with Microsoft Visual Studio and its useful features and c++ unit testing. The folder here includes a .sln solution file. Actual C++ source files can be found in the binaryTreeSort folder in this directory.
Included in this repo is also a main release executable that, given an input specification, will generate random numbers to create a tree and then output all the numbers to 3 files defined by the input. The command format for windows powershell is:
./binaryTreeSort.exe \<random numbers file\> \<greatest to least file\> \<least to greatest file\> \<number of random numbers\>

So a full entry line will look something like:

(directory)\dpgWinter18-19\binaryTreeSort\Release>  ./binaryTreeSort.exe './Release/<b>Results/randomNumFile.txt</b>' './Release/<b>Results\gtl.txt</b>' './Release/<b>Results/ltg.txt</b>' 100

this will generate 100 random numbers and save the results to the bolded files in the subfolder of Release called "Results"

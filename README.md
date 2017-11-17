# CSCI-315-Program
This is a repository for my CSCI 315 program that I am submitting as part of my Senior Portfolio.

### Program Information
This is a program that takes HTML files as input, and has output that first determines whether or not the passed file is a balanced, usable HTML file. Next, if it is balanced, it outputs how many unique, balanced, HTML pages the passed file can visit. If it is not balanced, it simply shows that it can visit no pages.

### How To Compile/Run
This program was written in C++, and then compiled in a Linux-based environment using G++. The executable was created as HTML-Parser.out, and has been uploaded as a release. This program needs to be passed HTML files, in order to do any actual work. In light of this, I have included a folder of four sample HTML files to use as input. Also, to avoid confusion about how to call the function, I have included a makefile that will call the function in the correct way, passing the sample HTML files. The best way to run this program is to download the source code, and call make run.

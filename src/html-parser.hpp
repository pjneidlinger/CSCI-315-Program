/*
 * Student Name: PJ Neidlinger
 * Program Name: HTML Parser
 * Creation Date: 10/17/2017
 * Last Modified Date: 10/18/2017
 * CSCI Course: CSCI 315
 * Grade Received: 100
 * Comments Regarding Design: Dr. West, the instructor for CSCI 315, created the main file and the html files
 * in the pages/ directory. He tasked us with creating the actual cpp file to parse html files, along with
 * the header file.
*/

#ifndef HTML_PARSER_HPP
#define HTML_PARSER_HPP
#include <string>

class HTMLParser {
    private:
        std::string *mTags;
        std::string *mFiles;
        int mSize;
        int mFileSize;
        int mHolds;
        int mFileHolds;
    public:
        HTMLParser();
        ~HTMLParser();
        void makeBigger();
        void fileBigger();
        void parse(std::string filename);
        void removePair(int closeIndex);
        bool isBalanced(std::string filename);
        int pageHelp(std::string filename);
        int pageVisitAmount(std::string filename);
};

#endif

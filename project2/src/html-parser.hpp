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

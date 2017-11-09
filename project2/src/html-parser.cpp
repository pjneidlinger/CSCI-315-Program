#include "html-parser.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;

HTMLParser::HTMLParser() {
  // Set initial values
  mSize = 0;
  mHolds = 100;
  // Create array and initialize all values to an empty string
  mTags = new string[mHolds];
  for (int i = 0; i < mHolds; i++) {
    mTags[i] = "";
  }

  // Set initial values for file tracking system
  mFileSize = 0;
  mFileHolds = 100;
  // Creates array and initialize all values to an empty string
  mFiles = new string[mFileHolds];
  for (int i = 0; i < mFileHolds; i++) {
    mFiles[i] = "";
  }
}

HTMLParser::~HTMLParser() {
  // Delete the pointers created on the heap
  delete[] mTags;
  delete[] mFiles;
}

// This is a function to make the mTags array bigger, if it is necessary
void HTMLParser::makeBigger() {
  // Set up a temp variable to hold the current values of mTags
  string temp[mSize];
  for (int i = 0; i < mSize; i++) {
    temp[i] = mTags[i];
  }
  // Delete the current value of mTags
  delete[] mTags;
  // Increment the array size by a factor of 10
  mHolds *= 10;
  mTags = new string[mHolds];
  // Initialize all array values to an empty string
  for (int i = 0; i < mHolds; i++) {
    mTags[i] = "";
  }
  // Add the original values of mTags back to the new array
  for (int i = 0; i < mSize; i++) {
    mTags[i] = temp[i];
  }
}

void HTMLParser::fileBigger() {
  // Set up a temp variable to hold the current values of mFiles
  string temp[mFileSize];
  for (int i = 0; i < mFileSize; i++) {
    temp[i] = mFiles[i];
  }
  // Delete the current value of mFiles
  delete[] mFiles;
  // Increment the array size by a factor of 10
  mFileHolds *= 10;
  mFiles = new string[mFileHolds];
  // Initialize all array values to an empty string
  for (int i = 0; i < mFileHolds; i++) {
    mFiles[i] = "";
  }
  // Add the original values of mFiles back to the new array
  for (int i = 0; i < mFileSize; i++) {
    mFiles[i] = temp[i];
  }
}

void HTMLParser::parse(std::string filename) {
  // Set mSize to 0 so each new file starts over in mTags
  mSize = 0;

  // Open file
  ifstream file;
  file.open(filename.c_str());

  // Check to ensure file is open
  if (!file.is_open()) {return;}

  // Add each tag as a new element in the mTags array
  string tag; char c;
  while (!file.eof()) {
    file.get(c);
    if (c == '<') {
      getline(file, tag, '>');

      // If the amount of tags has reached the size of the array, we need
      // to increase the size of the array
      if (mSize == mHolds) { makeBigger(); }

      mTags[mSize] = tag;
      mSize += 1;
    }
  }

  // Close the file
  file.close();
}

// This is a function to remove an opening and closing tag pair from the
// mTags array
void HTMLParser::removePair(int closeIndex) {
  // Remove the values by shifting everything else down
  for (int i = (closeIndex - 1); i < mSize; i++) {
    mTags[i] = mTags[i + 2];
  }
  // Make the last two indexes the empty string
  mTags[mSize - 2] = "";
  mTags[mSize - 1] = "";
  // Decrement the size of mTags by two
  mSize -= 2;
}

bool HTMLParser::isBalanced(std::string filename) {
  // Parse the passed file to get mSize and mTags data
  parse(filename);

  // If there are not an even number of tags, there are not an opening and
  // closing tag for each tag, so therefore it is not balanced
  if ((mSize % 2) != 0) { return false; }

  string temp;
  // Loop through all the values in the array
  for (int i = 0; i < mSize; i++) {
    // if a value is found that is a closing tag
    if ((mTags[i])[0] == '/') {
      // set up a temp variable to compare to the opening tag
      temp = (mTags[i]).substr(1, string::npos);
      // if the temp variable is an anchor tag, that means that the previous
      // location should contain an opening anchor tag, which holds more than
      // just the a tag, it holds a link to another file
      if (temp == "a") {
        // So, if the closing tag is an anchor tag, we will check to see if the
        // previous element is an opening anchor tag
        if ((mTags[i - 1])[0] == 'a') {
          // If it is, remove the pair, and decrement the iterator by 2
          removePair(i);
          i -= 2;
        }
        // If the previous element is not an anchor tag, return false because
        // the file is not balanced
        else { return false; }
      }
      // If the tag is anything other than an anchor tag, the tag should be
      // exactly equal to the prevous element in the array
      // If it is not, return false
      else if (mTags[i - 1] != temp) { return false; }
      // If it is, remove the pair and decrease the iterator by two
      else {
        removePair(i);
        i -= 2;
      }
    }
  }
  // If the function has reached here without returning false, it must be
  // balanced, and therefore we return true
  return true;
}

int HTMLParser::pageHelp(std::string filename) {
  // Check to ensure that the passed file is balanced, if not return 0
  if (!isBalanced(filename)) { return 0; }
  // Parse the file to get tag data
  parse(filename);

  // If mSize == 0, that means that the file did not exist, and we should
  // return -1 to subtract one visit amount from the rolling sum
  if (mSize == 0) { return -1; }

  // If we have already filled up the mFiles array, make it bigger
  if (mFileSize == mFileHolds) {
    fileBigger();
  }
  // Add the current file to the mFiles array, so that we cannot come back
  // to the file we are at right now
  mFiles[mFileSize] = filename;
  // Increment the size of mFiles
  mFileSize += 1;

  // Set up a temp array to hold the current values of mSize and mTags, because
  // the values of these things may get changed in subsequent calls to this
  // function
  int sum = 0;
  int size = mSize;
  string temp[mSize];
  for (int i = 0; i < size; i++) {
    temp[i] = mTags[i];
  }
  // Set up an empty string to hold the link to the next file
  string link = "";
  // Set up a continue variable to know when to stop looping
  bool cont = true;
  // Loop through every value in the temp array
  for (int i = 0; i < size; i++) {
    // If we get to an anchor tag
    if ((temp[i])[0] == 'a') {
      // Set link equal to the link in the reference
      link = temp[i].substr(7, string::npos);
      // Check to make sure that the file has not already been looked into
      for (int j = 0; ((j < mFileSize) && (cont == true)); j++) {
        if (link == mFiles[j]) {
          cont = false;
        }
      }
      // If the file has not already been seen
      if (cont) {
        // Increase the sum by one
        sum += 1;
        // If we have filled the array up entirely, increase it's size
        if (mFileSize == mFileHolds) {
          fileBigger();
        }
        // Set the last value in the array to be the link
        mFiles[mFileSize] = link;
        // Inrease the size of mFiles by one
        mFileSize += 1;
        // Recursively call and update the sum until it can reach no more files
        sum += pageHelp(link);
      }
      // Reset our continue variable to loop again
      cont = true;
    }
  }
  // Return the sum
  return sum;
}

int HTMLParser::pageVisitAmount(std::string filename) {
  // I have this function broken up into two functions, because the array of
  // files needs to be reset to nothing each time the pageVisitAmount function
  // is called, because each time this function is called, no files have been
  // seen, but every subsequent file that is delved into needs to know what
  // files have already been seen
  mFileSize = 0;
  return pageHelp(filename);
}

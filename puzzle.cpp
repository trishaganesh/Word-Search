#include <iostream>
#include <vector>
#include <string>
#include <ctype.h>
#include <unordered_set>


using namespace std;

//puzzleSearch struct - searching through a puzzle
struct puzzleSearch
{
   bool elementEnd;
   puzzleSearch *childNodes[100000];
   puzzleSearch() : elementEnd(false) {}
};

//function to generate a puzzle
puzzleSearch *generateAPuzzle(vector<string> &wordDictionary) {
   puzzleSearch *main = new puzzleSearch();
   for (int x = 0; x < wordDictionary.size(); ++x) {
       string element = wordDictionary[x];
       puzzleSearch *currElement = main;
       for (int y = 0; y < element.length(); ++y) {
           char str = tolower(element[y]);
           puzzleSearch *numElements = NULL;
           if (currElement->childNodes[str - 'a'] == NULL) {
               numElements = new puzzleSearch();
               currElement->childNodes[str - 'a'] = numElements;
           } else {
               numElements = currElement->childNodes[str - 'a'];
           }
           if (y + 1 == element.length()) {
               numElements -> elementEnd = true;
           }
           currElement = numElements;
       }
   }
   return main;
}

// no duplicates 
void wordFinding(vector< vector<char>> &puzzleCheck, const puzzleSearch *mainWordDictionary,
                               unordered_set<string> &results, vector<char> &currentElementFinding,
                               vector< vector<bool> > &searchPuzzleTable, int x, int y) {
   searchPuzzleTable[x][y] = true;
   char str = puzzleCheck[x][y];
   puzzleSearch *curNode = mainWordDictionary->childNodes[str - 'a'];
   if (curNode == NULL) {
       searchPuzzleTable[x][y] = false;
       return;
   }
   
   currentElementFinding.push_back(str);
   //condition - check word
   if (curNode -> elementEnd) { 
       string str2(currentElementFinding.begin(), currentElementFinding.end());
       results.insert(str2);
       //continue
   }
   // every direction within the puzzle
   if (x - 1 >= 0 && !searchPuzzleTable[x - 1][y])
       wordFinding(puzzleCheck, curNode, results, currentElementFinding, searchPuzzleTable, x - 1, y);

   if (x + 1 < puzzleCheck[0].size() && !searchPuzzleTable[x + 1][y])
       wordFinding(puzzleCheck, curNode, results, currentElementFinding, searchPuzzleTable, x + 1, y);
       
   if (y - 1 >= 0 && !searchPuzzleTable[x][y - 1])
       wordFinding(puzzleCheck, curNode, results, currentElementFinding, searchPuzzleTable, x, y - 1);
       
   if (y + 1 < puzzleCheck.size() && !searchPuzzleTable[x][y + 1])
       wordFinding(puzzleCheck, curNode, results, currentElementFinding, searchPuzzleTable, x, y + 1);
       
   if (x - 1 >= 0 && y - 1 >= 0 && !searchPuzzleTable[x - 1][y - 1])
       wordFinding(puzzleCheck, curNode, results, currentElementFinding, searchPuzzleTable, x - 1, y - 1);
       
   if (x - 1 >= 0 && y + 1 < puzzleCheck.size() && !searchPuzzleTable[x - 1][y + 1])
       wordFinding(puzzleCheck, curNode, results, currentElementFinding, searchPuzzleTable, x - 1, y + 1);
       
   if (x + 1 < puzzleCheck[0].size() && y - 1 >= 0 && !searchPuzzleTable[x + 1][y - 1])
       wordFinding(puzzleCheck, curNode, results, currentElementFinding, searchPuzzleTable, x + 1, y - 1);
       
   if (x + 1 < puzzleCheck[0].size() && y + 1 < puzzleCheck.size() && !searchPuzzleTable[x + 1][y + 1])
       wordFinding(puzzleCheck, curNode, results, currentElementFinding, searchPuzzleTable, x + 1, y + 1);
       
   searchPuzzleTable[x][y] = false;
   currentElementFinding.pop_back();
}

//define the function findAllWordsInPuzzle to search all the elements n the puzzle
unordered_set<string> findAllWordsInPuzzle(vector< vector<char> > &puzzleCheck, puzzleSearch *mainWordDictionary) {
   unordered_set<string> results;
   vector<char> currentElementFinding;
   vector< vector<bool>> searchPuzzleTable;
   for (int x = 0; x < puzzleCheck.size(); ++x) {
       searchPuzzleTable.push_back(vector<bool> (puzzleCheck[x].size(), false));
   }
   for (int x = 0; x < puzzleCheck.size(); ++x) {
       for (int y = 0; y < puzzleCheck[y].size(); ++y) {
         
         //call function
           wordFinding(puzzleCheck, mainWordDictionary, results, currentElementFinding, searchPuzzleTable, x, y);
       }
   }
   return results;
}

//start the main function
int main() {
  //test any words, puzzle.txt file (open file)
   vector<string> elementList {"that", "there", "here", "hello", "hat", "of", "ago"};
   
   //calling function
   puzzleSearch *mainWordDictionary = generateAPuzzle(elementList);
   
   // create the puzzle box
   vector<char> row1 {'t', 'i', 'h', 's'};
   vector<char> row2 {'w', 'a', 't', 's'};
   vector<char> row3 {'o', 'a', 'h', 'g'};
   vector<char> row4 {'f', 'g', 'd', 't'};
   vector<char> row5 {'l', 'p', 't', 'e'};

   vector< vector<char>> puzzleCheck;
   
   // create a vector to store the puzzle elements
   puzzleCheck.push_back(row1);
   puzzleCheck.push_back(row2);
   puzzleCheck.push_back(row3);
   puzzleCheck.push_back(row4);
   puzzleCheck.push_back(row5);
   
   //call the function findAllWordsInPuzzle to find the words
   unordered_set<string> results = findAllWordsInPuzzle(puzzleCheck, mainWordDictionary);
   
   cout<<"Words found are listed: \n";
   
   //display the result
   for (auto start = results.begin(); start != results.end(); ++start) {
       cout << *start << endl;
   }
   return 0;
}

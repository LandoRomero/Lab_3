**3/12/2025**
* file name(s) and/or file/folder structure/capitalization do not comply with posted instructions;  file with main() – main.cpp, input files- "in_\*.txt”, output –“out_\*.txt”, error –“err_\*.txt”; do not include any other files or folders -2
* * inadequate and/ insufficient test data/ not all possible cases have been tested: e.g. each record has 4 pieces of data; pow(2,4)->16  possible combinations of valid/invalid and only one of them is a valid record; all menu options should be tested;  no zeros, negative numbers, etc -5
* multiple return statements in a non-recursive function; may result in unreachable return; use if/else, use a variable to store the results and return the variable; e.g. a function to check the length of a string, function to validate account number,   short validations can be done in the return statement; e.g.  return a<MIN_LENGTH);  -5
* excessive use of printf/cout/cin/ file stream/stringstream and/or endl and/or << >>; applies to all output, not just menu-5
```
//e.g.
cout << "\n\nMenu:\n”
“1. Encrypt\n”
“2. Decrypt\n”
“3. Quit\n"<<endl;
```
* << not needed between strings
* put ‘\n’ is at the end of the previous whenever possible  
* Should print a couple of blank lines before the menu to separate from the lines of text above it
* no need for the “.” at the end of menu options; it is just clutter but no useful info to a user* no need for the “.” at the end of menu options; it is just clutter but no useful info to a user
 	* input>>name>>id>gpal;* 
*  function definitions above main() -10
* #190-194 redundant; should create a highly re-usable function that takes an error message string as a parameter, clears the failed input, and outputs custom error messages -2
* cin.ignore(…); what will happen if a use enters +1  more chars than you specified; -2
* all menus should be implemented using the same logic switch with enum , regardless of the number of options -2
* #188 what for? read the file till eof -2
* cannot test – requires interactive input, stopped grading

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
* must be able to process an unlimited number of expressions
* is it a good idea to ask a user to enter an expression for this program? I am sure you can think of a faster and more efficinet way of doing it
* cannot test – requires interactive input, stopped grading


**3/19/2025**
* class definition style & standards:  first vars and do not forget to initialize;  functions: separate group of functions  by a blank line; either matching setter/getter pairs or list all setters back to back  and list all getters back to back; start with default c’tor, followed by other c’tors in the order of increased number of arguments, d’tor- right after c’tor(s), overloaded functions- list them back to back in the order of increased number of arguments;  all accessor/getter functions should be const; all functions with more than one statement should be normal (defined externally), no inline functions with more than one statement; initialize all member variables to appropriate default values at the time of definition
* modularization: each menu option should have its own function with a possible exception of the QUIT case; -5
* const; if it is not 1 or 0 make it const; in case of ASCII values, use chars, e.g., temp>’a’  -5 
* inline functions do not adhere to the best practices -5
* multiple return statements in a non-recursive function; may result in unreachable return; use if/else, use a variable to store the results and return the variable; e.g. a function to check the length of a string, function to validate account number,   short validations can be done in the return statement; e.g.  return a<MIN_LENGTH);  -5
* what’s the value of token if the top<0? -1
* cin.ignore(…); what will happen if a use enters +1  more chars than you specified; -2
* uses continue and/or break (Ok in switch) and/or go to and/or exit() in loop(s) and/or if(s) and/or empty return (e.g., return;) infinite loops (while(true) or similar); there is no situation where same effect cannot be achieved by a logical statement; in other words, there is no situation in this realm that cannot be described by using a combination of relational, comparison, and logical operators; you can always  write a loop condition to exit naturally when needed; see the syllabus – stopped grading

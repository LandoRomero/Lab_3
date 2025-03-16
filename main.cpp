#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

const int MAX_EXPR_LENGTH = 60;
const int MAX_STACK_SIZE = 60;

struct Token {
    char symbol[6];
};

class Stack {
    Token items[MAX_STACK_SIZE];
    int top;
public:
    Stack() : top(-1) {}
    bool push(const char* token) {
        if(top >= MAX_STACK_SIZE - 1)
            return false;
        top++;
        strcpy(items[top].symbol, token);
        return true;
    }
    bool pop(Token &token) {
        if(top < 0)
            return false;
        strcpy(token.symbol, items[top].symbol);
        top--;
        return true;
    }
    bool isEmpty() const {
        return top < 0;
    }
    bool peek(Token &token) const {
        if(top < 0)
            return false;
        strcpy(token.symbol, items[top].symbol);
        return true;
    }
};

void clearInputStream(const string &errorMsg) {
    cin.clear();
    cin.ignore(1000, '\n');
    cout << errorMsg << "\n";
}

bool tokensMatch(const char* open, const char* close) {
    if(strcmp(open, "(") == 0 && strcmp(close, ")") == 0)
        return true;
    if(strcmp(open, "{") == 0 && strcmp(close, "}") == 0)
        return true;
    if(strcmp(open, "[") == 0 && strcmp(close, "]") == 0)
        return true;
    if(strcmp(open, "<!--") == 0 && strcmp(close, "-->") == 0)
        return true;
    if(strcmp(open, "/*") == 0 && strcmp(close, "*/") == 0)
        return true;
    if(strcmp(open, "\"") == 0 && strcmp(close, "\"") == 0)
        return true;
    if(strcmp(open, "\'") == 0 && strcmp(close, "\'") == 0)
        return true;
    return false;
}

bool isClosingToken(const char* token) {
    return (strcmp(token, ")") == 0 ||
            strcmp(token, "}") == 0 ||
            strcmp(token, "]") == 0 ||
            strcmp(token, "-->") == 0 ||
            strcmp(token, "*/") == 0);
}

bool isSymmetricToken(const char* token) {
    return (strcmp(token, "\"") == 0 ||
            strcmp(token, "\'") == 0);
}

bool isOpeningToken(const char* token) {
    return (strcmp(token, "(") == 0 ||
            strcmp(token, "{") == 0 ||
            strcmp(token, "[") == 0 ||
            strcmp(token, "<!--") == 0 ||
            strcmp(token, "/*") == 0);
}

bool processExpression(const char* expr, char* symbolsOnly) {
    Stack stack;
    symbolsOnly[0] = '\0';
    bool balanced = true;
    int len = strlen(expr);

    for (int i = 0; i < len; ) {
        char token[6] = "";
        bool foundToken = false;

        if(i <= len - 4 && strncmp(&expr[i], "<!--", 4) == 0) {
            strcpy(token, "<!--");
            i += 4;
            foundToken = true;
        }
        else if(i <= len - 3 && strncmp(&expr[i], "-->", 3) == 0) {
            strcpy(token, "-->");
            i += 3;
            foundToken = true;
        }
        else if(i <= len - 2 && strncmp(&expr[i], "/*", 2) == 0) {
            strcpy(token, "/*");
            i += 2;
            foundToken = true;
        }
        else if(i <= len - 2 && strncmp(&expr[i], "*/", 2) == 0) {
            strcpy(token, "*/");
            i += 2;
            foundToken = true;
        }
        else if(expr[i] == '\"') {
            strcpy(token, "\"");
            i++;
            foundToken = true;
        }
        else if(expr[i] == '\'') {
            strcpy(token, "\'");
            i++;
            foundToken = true;
        }
        else if(expr[i] == '(' || expr[i] == ')' ||
                expr[i] == '{' || expr[i] == '}' ||
                expr[i] == '[' || expr[i] == ']') {
            token[0] = expr[i];
            token[1] = '\0';
            i++;
            foundToken = true;
        }
        else {
            i++;
        }

        if(foundToken) {
            strcat(symbolsOnly, token);
            strcat(symbolsOnly, " ");
            if(isSymmetricToken(token)) {
                Token topToken;
                if(!stack.isEmpty()) {
                    stack.peek(topToken);
                    if(strcmp(topToken.symbol, token) == 0)
                        stack.pop(topToken);
                    else
                        stack.push(token);
                }
                else {
                    stack.push(token);
                }
            }
            else if(isOpeningToken(token)) {
                stack.push(token);
            }
            else if(isClosingToken(token)) {
                Token topToken;
                if(stack.isEmpty() || !stack.peek(topToken) || !tokensMatch(topToken.symbol, token)) {
                    balanced = false;
                } else {
                    Token popped;
                    stack.pop(popped);
                }
            }
        }
    }

    if(!stack.isEmpty())
        balanced = false;

    return balanced;
}

enum MenuOptions {
    PROCESS_EXPRESSIONS = 1,
    QUIT = 2
};

int main() {
    const char* inFileName = "in_expr.txt";
    const char* outFileName = "out_expr.txt";
    const char* errFileName = "err_expr.txt";

    ofstream errFile(errFileName);
    if(!errFile) {
        cout << "Error: Could not open error file.\n";
        return 1;
    }

    int choice = 0;

    do {
        cout << "\n\n";
        cout << "Menu:\n";
        cout << "1. Process expressions from file\n";
        cout << "2. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if(cin.fail()){
            clearInputStream("Invalid input. Please enter a valid option (1 or 2).");
            continue;
        }
        switch(choice) {
            case PROCESS_EXPRESSIONS: {
                ifstream inFile(inFileName);
                if(!inFile) {
                    errFile << "Error: Unable to open input file " << inFileName << "\n";
                    cout << "Error: Unable to open input file " << inFileName << "\n";
                    break;
                }
                ofstream outFile(outFileName);
                if(!outFile) {
                    errFile << "Error: Unable to open output file " << outFileName << "\n";
                    cout << "Error: Unable to open output file " << outFileName << "\n";
                    break;
                }
                outFile << "--------------------------------------------------------------------------\n";
                outFile << left << setw(35) << "Original Expression"
                        << left << setw(30) << "Symbols Only"
                        << "Well-Formed" << "\n";
                outFile << "--------------------------------------------------------------------------\n";
                char expr[256];
                int lineCount = 0;
                while(inFile.getline(expr, sizeof(expr))) {
                    lineCount++;
                    if(strlen(expr) > MAX_EXPR_LENGTH) {
                        errFile << "Error on line " << lineCount << ": Expression exceeds "
                                << MAX_EXPR_LENGTH << " characters. Expression skipped.\n";
                        continue;
                    }
                    char symbolsOnly[512] = "";
                    bool balanced = processExpression(expr, symbolsOnly);
                    outFile << left << setw(35) << expr;
                    outFile << left << setw(30) << symbolsOnly;
                    outFile << (balanced ? "Yes" : "No") << "\n";
                }
                outFile << "--------------------------------------------------------------------------\n";
                cout << "Processing complete. Exit the program and check " << outFileName << " for results.\n";
                inFile.close();
                outFile.close();
                break;
            }
            case QUIT:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid option. Please try again.\n";
                break;
        }
        cin.ignore(1000, '\n');
    } while(choice != QUIT);

    errFile.close();
    return 0;
}

/*
Test Runs:

Assuming the input file "in_expr.txt" contains:
---------------------------------------------
(hkj   hkj{hj  shj})
(hkj   hkj{)hj  shj}
<!--Hello-->
/* Comment */                       /*
---------------------------------------------


When choosing option 1 from the menu, the program reads each line and writes the output table to "out_expr.txt". For instance, the output table might look like:

--------------------------------------------------------------------------
Original Expression                Symbols Only                  Well-Formed
--------------------------------------------------------------------------
(hkj   hkj{hj  shj})                ( { } )                     Yes
(hkj   hkj{)hj  shj}                ( { ) }                     No
<!--Hello-->                        <!--  -->                   Yes
/* Comment */                       /*  */              /*      Yes
--------------------------------------------------------------------------

Error messages for any expression that is too long will be written to "err_expr.txt".
*/


#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

const int MAX_EXPR_LENGTH = 60;
const int MAX_EXPRESSIONS = 10;
const int MAX_STACK_SIZE = 60;

struct Token {
    char symbol[6];
};

class Stack {
    Token items[MAX_STACK_SIZE];
    int top;
public:
    Stack() { top = -1; }
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

bool processExpression(const char* expr, char* symbolsOnly, bool &isBalanced) {
    Stack stack;
    symbolsOnly[0] = '\0';
    isBalanced = true;
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
                    if(strcmp(topToken.symbol, token) == 0) {
                        Token popped;
                        stack.pop(popped);
                    }
                    else {
                        stack.push(token);
                    }
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
                    isBalanced = false;
                    return isBalanced;
                }
                else {
                    Token popped;
                    stack.pop(popped);
                }
            }
        }
    }
    if(!stack.isEmpty())
        isBalanced = false;
    return isBalanced;
}

int main() {
    int choice;
    char expressions[MAX_EXPRESSIONS][MAX_EXPR_LENGTH+1];
    char symbolsOnly[MAX_EXPRESSIONS][256];
    bool balancedResults[MAX_EXPRESSIONS];
    int count = 0;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Process all expressions" << endl;
        cout << "2. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        if(choice == 1) {
            bool validCount = false;
            while (!validCount) {
                cout << "\nEnter the number of expressions (max " << MAX_EXPRESSIONS << "): ";
                cin >> count;
                if(cin.fail()){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input. Please enter a number between 1 and " << MAX_EXPRESSIONS << "." << endl;
                }
                else if(count < 1 || count > MAX_EXPRESSIONS) {
                    cout << "Error: Number of expressions must be between 1 and " << MAX_EXPRESSIONS << "." << endl;
                }
                else {
                    validCount = true;
                }
            }
            cin.ignore();
            for (int i = 0; i < count; i++) {
                cout << "Enter expression " << (i+1) << ": ";
                cin.getline(expressions[i], MAX_EXPR_LENGTH+100);
                if(strlen(expressions[i]) > MAX_EXPR_LENGTH) {
                    cout << "Error: Expression exceeds " << MAX_EXPR_LENGTH << " characters. Skipping this expression." << endl;
                    expressions[i][0] = '\0';
                    symbolsOnly[i][0] = '\0';
                    balancedResults[i] = false;
                }
                else {
                    processExpression(expressions[i], symbolsOnly[i], balancedResults[i]);
                }
            }
            cout << "\n--------------------------------------------------------------------------" << endl;
            cout << left << setw(35) << "Original Expression"
                 << left << setw(30) << "Symbols Only"
                 << "Well-Formed" << endl;
            cout << "--------------------------------------------------------------------------" << endl;
            for (int i = 0; i < count; i++) {
                cout << left << setw(35) << expressions[i];
                cout << left << setw(30) << symbolsOnly[i];
                cout << (balancedResults[i] ? "Yes" : "No") << endl;
            }
            cout << "--------------------------------------------------------------------------" << endl;
        }
        else if(choice != 2) {
            cout << "Invalid option. Please try again." << endl;
        }
    } while(choice != 2);
    return 0;
}

/*
Test Runs:

Menu:
1. Process all expressions
2. Quit
Enter your choice: 1

Enter the number of expressions (max 10): 15
Error: Number of expressions must be between 1 and 10.

Enter the number of expressions (max 10): abc
Invalid input. Please enter a number between 1 and 10.

Enter the number of expressions (max 10): 2
Enter expression 1: (hkj   hkj{hj  shj})
Enter expression 2: (hkj   hkj{)hj  shj}

--------------------------------------------------------------------------
Original Expression                Symbols Only                  Well-Formed
--------------------------------------------------------------------------
(hkj   hkj{hj  shj})                ( { } )                     Yes
(hkj   hkj{)hj  shj}                ( { ) }                     No
--------------------------------------------------------------------------

Menu:
1. Process all expressions
2. Quit
Enter your choice: 2
*/

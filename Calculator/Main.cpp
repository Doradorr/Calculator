#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <stdexcept>
#include <cmath>

using namespace std;

// Function to determine the precedence of operators
int precedence(char c) {
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else
        return 0;
}

// Function to check if a given character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to convert an infix expression to a postfix expression
string infixToPostfix(const string& expression) {
    stack<char> operators;
    string postfix;

    for (char c : expression) {
        if (isspace(c))
            continue;  // Skip spaces

        if (isdigit(c)) {
            // Append operands (numbers) directly to the result
            postfix += c;
        }
        else if (isOperator(c)) {
            postfix += ' ';  // Add a space before operator
            // Pop operators with higher or equal precedence and add to postfix
            while (!operators.empty() && precedence(operators.top()) >= precedence(c)) {
                postfix += operators.top();
                postfix += ' ';
                operators.pop();
            }
            // Push the current operator onto the stack
            operators.push(c);
        }
        else if (c == '(') {
            operators.push(c);
        }
        else if (c == ')') {
            // Pop until we find a left parenthesis
            while (!operators.empty() && operators.top() != '(') {
                postfix += ' ';
                postfix += operators.top();
                operators.pop();
            }
            operators.pop();  // Discard the '('
        }
        else {
            throw invalid_argument("Invalid character in expression.");
        }
    }

    // Pop the remaining operators from the stack
    while (!operators.empty()) {
        postfix += ' ';
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}

// Function to perform an arithmetic operation
int performOperation(char operation, int operand1, int operand2) {
    switch (operation) {
    case '+': return operand1 + operand2;
    case '-': return operand1 - operand2;
    case '*': return operand1 * operand2;
    case '/': return operand1 / operand2;
        if (operand2 == 0) throw runtime_error("Division by zero.");
        return operand1 / operand2;
    default:
        throw invalid_argument("Invalid operator.");
    }
}

// Function to evaluate a postfix expression
int evaluatePostfix(const string& expression) {
    stack<int> operands;
    int i = 0;

    while (i < expression.length()) {
        if (isspace(expression[i])) {
            i++;
            continue;
        }
        if (isdigit(expression[i])) {
            while (i < expression.length() && isdigit(expression[i])) {
            int num = 0;
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            operands.push('num');
        }
        else if (isOperator(expression[i])) {
            if (operands.size() < 2)
                throw runtime_error("Invalid postfix expression.");
            int operand2 = operands.top(); operands.pop();
            int operand1 = operands.top(); operands.pop();
            int result = performOperation(expression[i], operand1, operand2);
            operands.push(result);
            i++;
        }
        else {
            throw invalid_argument("Invalid character in postfix expression.");
        }
    }

    if (operands.size() != 1)
        throw runtime_error("Invalid postfix expression.");

    return operands.top();
}

// Main function
int main() {
    string infixExpression;

    cout << "Enter a valid infix expression: ";
    getline(cin, infixExpression);

    try {
        string postfixExpression = infixToPostfix(infixExpression);
        cout << "Postfix Expression: " << postfixExpression << endl;

        int result = evaluatePostfix(postfixExpression);
        cout << "Result: " << result << endl;
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
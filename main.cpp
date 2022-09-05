#include<iostream>
#include<string>
#include<fstream>
#include<list>

using namespace std;
ifstream fin("date.in");

class Node {
public:
    char info;
    Node *left = nullptr, *right = nullptr;

    Node(char info) {
        this->info = info;
        this->right = nullptr;
        this->left = nullptr;
    }
};

class Stack {
public:
    Node *tree_node;
    Stack *next;

    Stack(Node *aux) {
        tree_node = aux;
        next = nullptr;
    }
};

class Expression {
private:
    Stack *top;

public:
    Expression() {
        top = nullptr;
    }

    void push(Node *x);

    Node *pop();

    Node *getTop();

    void add(char ch);

    void MakeTree(list<char> exp);

    double calculate();

    double calculate(Node *x);

    void PostFix();

    void PostOrder(Node *x);
};


void Expression::push(Node *x) {
    if (top == nullptr)
        top = new Stack(x);
    else {
        Stack *y = new Stack(x);
        y->next = top;
        top = y;
    }
}

Node *Expression::pop() {
    if (top != nullptr) {
        Node *x = top->tree_node;
        top = top->next;
        return x;
    }
}

Node *Expression::getTop() {
    return top->tree_node;
}

void Expression::add(char ch) {
    if (ch >= '0' && ch <= '9') {
        Node *y = new Node(ch);
        push(y);
    } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
        Node *y = new Node(ch);
        y->left = pop();
        y->right = pop();
        push(y);
    }
}

void Expression::MakeTree(list<char> exp) {
    int i;
    for (i = exp.size() - 1; i >= 0; i--) {
        auto exp_index = exp.begin();
        advance(exp_index, i);
        add(*exp_index);                      //getting the element at given index from the list exp
    }

}

double Expression::calculate() {
    return calculate(getTop());
}

double Expression::calculate(Node *x) {
    if (x->left == nullptr && x->right == nullptr)
        return (x->info) - '0';
    else {
        double rez = 0;
        double left = calculate(x->left);
        double right = calculate(x->right);
        char symbol = x->info;
        if (symbol == '+')
            rez = left + right;
        else if (symbol == '-')
            rez = left - right;
        else if (symbol == '*')
            rez = left * right;
        else if (symbol == '/')
            rez = left / right;
        else
            rez = left + right;
        return rez;
    }
}

void Expression::PostFix() {
    PostOrder(getTop());
}

void Expression::PostOrder(Node *x) { //recursive tree traversal for postorder
    if (x != nullptr) {
        PostOrder(x->left);
        PostOrder(x->right);
        cout << x->info;
    }
}

void display_list(list<char> x) //display the created list
{
    list<char>::iterator i;
    for (i = x.begin(); i != x.end(); ++i)
        cout << *i;
    cout << '\n';
}

int main() {
    string str;
    Expression exp;
    cout << "Expression: ";
    getline(fin, str);
    int count_parentheses = 0;
    list<char> l;
    for (int i = 0; i <= str.length() - 1; i++) {
        if (str[i] != ' ')
            l.push_back(str[i]);
        if (str[i] == '(')
            count_parentheses++;
        else if (str[i] == ')')
            count_parentheses--;
    }
    if (count_parentheses != 0) {
        cout << "Expression is invalid. Please check parentheses!";
        return 0;
    }
    exp.MakeTree(l);
    exp.PostFix();
    cout << endl;
    cout << "End result is: " << exp.calculate();
    fin.close();
    return 0;
}
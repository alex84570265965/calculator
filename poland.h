#include <cmath>

using namespace std;

const long double eps = 0.000001;

struct Stack {
    long double num;
    char zn;
    Stack *next;
};

void push(Stack *&t, long double x, char ch) {
    Stack *h = (Stack *) malloc(sizeof(Stack));
    (*h).zn = ch;
    (*h).num = x;
    (*h).next = t;
    t = h;
}

Stack pop(Stack *&t) {
    Stack h = *t;
    t = (*t).next;
    return h;
}

int prior(char ch) {
    if (ch == '(') {
        return 0;
    }
    if (ch == '+' || ch == '-') {
        return 1;
    }
    if (ch == '*' || ch == '/') {
        return 2;
    }
    if (ch == '^'){
        return 3;
    }
    return 4;
}

bool op(char ch) {
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
        return true;
    } else {
        return false;
    }
}

bool prr(char ch) {
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '('  || ch == ')') {
        return true;
    } else {
        return false;
    }
}

bool apply(Stack *&t, char ch) {
    if(op(ch)) {
        long double b = (pop(t)).num;
        long double a = (pop(t)).num;
        if (ch == '+') push(t, a + b, '#');
        if (ch == '-') push(t, a - b, '#');
        if (ch == '*') push(t, a * b, '#');
        if (ch == '/') {
            if (fabs(b) < eps) {
                return false;
            } else {
                push(t, a / b, '#');
            }
        }
        if(ch == '^') {
            push(t, pow(a, b), '#');
        }
    }
    else{
        long double a = (pop(t)).num;
        if(ch == 'q') {
            if (a < 0.0) {
                return false;
            }
            else{
                push(t, sqrt(a), '#');
            }
        }
        if(ch == 's'){
            push(t, sin(a), '#');
        }
        if(ch == 'c'){
            push(t, cos(a), '#');
        }
        if(ch == 't') {
            if (cos(a) == 0.0) {
                return false;
            }
            else{
                push(t, sin(a) / cos(a), '#');
            }
        }
        if(ch == 'l'){
            if(a <= 0.0){
                return false;
            }
            push(t, log(a), '#');
        }
        if(ch == 'a'){
            push(t, fabs(a), '#');
        }
    }
    return true;
}

bool f(char ch){
    if(ch == 'q' || ch == 's' || ch == 'c' || ch == 't' || ch == 'l' || ch == 'a'){
        return true;
    }
    else{
        return false;
    }
}

int err(string s) {
    int sz = s.size() - 1;
    if (op(s[0]) && s[0] != '-') {
        return 1;
    }
    if (op(s[sz])) {
        return 1;
    }
    int p = 0;
    for (auto i : s) {
        if (i == '(') {
            p++;
        }
        if (i == ')') {
            p--;
        }
        if (p < 0) {
            return 1;
        }
    }
    if (p != 0) {
        return 1;
    }
    for (int i = 0; i < sz; i++) {
        if (op(s[i]) && op(s[i + 1])) {
            return 1;
        }
    }
    for (int i = 0; i < sz; i++) {
        if (s[i] == '(' && op(s[i + 1]) && s[i + 1] != '-') {
            return 1;
        }
    }
    for (int i = 0; i < sz; i++) {
        if (s[i + 1] == ')' && op(s[i])) {
            return 1;
        }
    }
    for(int i = 0; i < sz; i++){
        if(f(s[i]) && f(s[i + 1])){
            return 1;
        }
    }
    for(int i = 0; i < sz; i++){
        if(f(s[i]) && s[i + 1] != '('){
            return 1;
        }
    }
    for(int i = 0; i < sz; i++){
        if(s[i] == '(' && s[i + 1] == ')'){
            return 1;
        }
    }
    return 0;
}


string iz(string s){
    string s1;
    for(int i = 0; i < s.size(); i++){
        if(s[i] >= 'a' && s[i] <= 'z'){
            if(s[i] == 's' && s[i + 1] == 'q' ){
                s1 += 'q';
            }
            if(s[i] == 'a' && s[i + 1] == 'b' ){
                s1 += 'a';
            }
            if(s[i] == 's' && s[i + 1] == 'i'){
                s1 += 's';

            }
            if(s[i] == 'c' && s[i + 1] == 'o'){
                s1 += 'c';

            }
            if(s[i] == 't' && s[i + 1] == 'g'){
                s1 += 't';

            }
            if(s[i] == 'l' && s[i + 1] == 'n'){
                s1 += 'l';
            }

        }
        else{
            if(s[i] == '-' && s[i - 1] == '('){
                s1 += "0-";
            }
            else{
                s1 += s[i];
            }
        }
    }
    return s1;
}

int check(string s){
    int d = 0;
    for (int i = 0; i < s.size(); i++) {
        if(s[i] == '.'){
            continue;
        }
        if (d == 0) {
            if (!prr(s[i]) && !(s[i] >= '0' && s[i] <= '9')) {
                if (s[i] == 's' && s[i + 1] == 'i' && s[i + 2] == 'n') {
                    d = 2;
                    continue;
                }
                if (s[i] == 'c' && s[i + 1] == 'o' && s[i + 2] == 's') {
                    d = 2;
                    continue;
                }
                if (s[i] == 't' && s[i + 1] == 'g') {
                    d = 1;
                    continue;
                }
                if (s[i] == 'l' && s[i + 1] == 'n') {
                    d = 1;
                    continue;
                }
                if (s[i] == 's' && s[i + 1] == 'q' && s[i + 2] == 'r' && s[i + 3] == 't') {
                    d = 3;
                    continue;
                }
                return 1;
            }
        }
        if(d > 0){
            d--;
        }
    }
    return 0;
}

bool calculate(string s, long double & ans){
    int pr = 0;
    long double n = 0;
    s = '(' + s + ')';
    s = iz(s);
    Stack *top1 = nullptr, *top2 = nullptr;
    char c;
    int r = 0;
    long double tt = 1;
    for (int i = 0; i < s.size(); i++) {
        c = s[i];
        if (c == '.'){
            r = 1;
            continue;
        }
        if (c >= '0' && c <= '9') {
            if(r == 0){
                n *= 10;
                n += (c - '0');
                pr = 1;
            }
            else{
                tt *= 0.1;
                n += ((c - '0') * tt);
                pr = 1;
            }
            continue;
        }
        else {
            if (pr == 1) {
                push(top1, n, '#');
            }
            n = 0;
            pr = 0;
            tt = 1;
            r = 0;
        }
        if (c == '(') {
            push(top2, 0.0, c);
            continue;
        }
        if (c == ')') {
            char h = (pop(top2)).zn;
            while (h != '(') {
                bool q = apply(top1, h);
                if(q == false){
                    return false;
                }
                h = (pop(top2)).zn;
            }
        } else {
            while (top2 != nullptr && prior(c) <= prior((*top2).zn)) {
                bool q = apply(top1, (pop(top2)).zn);
                if(q == false){
                    return false;
                }
            }
            push(top2, 0.0, c);
        }
    }
    while (top2 != nullptr) {
        bool q = apply(top1, (pop(top2)).zn);
        if(q == false){
            return false;
        }
    }
    ans = (*top1).num;
    return true;
}


#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <stack>
#include <map>

#define DEBUG 1

enum TYPE {
	NONE_TYPE,
	NUMBER_TYPE, 
	VARIABLE_TYPE,
 	EVALUATABLE_TYPE, 
	LBRACKET_TYPE, 
	RBRACKET_TYPE,
	ASSIGN_TYPE
};

class Lexem {
  public:
  	Lexem();
  	virtual void print() {}
  	virtual TYPE get_type() = 0;
};

Lexem::Lexem() {}

class Number : public Lexem {
	int value;
  public:
  	Number();
  	Number(int);
  	int get_value();
  	void print();
  	TYPE get_type();
};

Number::Number() {}

Number::Number(int num) {
	value = num;
}

int Number::get_value() {
	return value;
}

void Number::print() {
	std::cout << value;
}

TYPE Number::get_type() {
	return NUMBER_TYPE;
}

enum OPERATOR {
	LBRACKET, RBRACKET,
	ASSIGN,
	OR,
	AND,
	BITOR,
	XOR,
	BITAND,
	EQ, NEQ,
	LEQ, LT, 
	GEQ, GT,
	SHL, SHR,
	PLUS, MINUS,
	MULT, DIV, MOD
};

int PRIORITY [] = {
	-1 , -1 ,
	0,
	1,
	2,
	3,
	4,
	5,
	6, 6,
	7, 7,
	7, 7,
	8, 8,
	9, 9,
	10 , 10 , 10,
	-1, -1
};

std::string OPERTEXT [] = {
	"(", ")",
	"=" ,
	"or" ,
	"and" ,
	"|",
	"^",
	"&",
	"==" , "!=" ,
	"<=" , "<" ,
	">=" , ">" ,
	"<<" , ">>" ,
	"+" , "-" ,
	"*", "/", "%",
	"goto", ":"
};

class Oper : public Lexem {
	OPERATOR opertype;
  public:
  	Oper();
  	Oper(std::string);
  	TYPE get_type();
  	void print();
  	int get_priority();
  	OPERATOR get_oper_type();
};

Oper::Oper() {}

OPERATOR Oper::get_oper_type() {
	return opertype;
}

void Oper::print() {
	if (opertype == PLUS) {
		std::cout << '+';
	} else if (opertype == MINUS) {
		std::cout << '-';
	} else if (opertype == LBRACKET) {
		std::cout << '(';
	} else if (opertype == RBRACKET) {
		std::cout << ')';
	} else if (opertype == MULT) {
		std::cout << '*';
	} else if (opertype == DIV) {
		std::cout << '/';
	} else if (opertype == MOD) {
		std::cout << '%';
	} else if (opertype == ASSIGN) {
		std::cout << '=';
	} else if (opertype == BITAND) {
		std::cout << '&';
	} else if (opertype == BITOR) {
		std::cout << '|';
	} else if (opertype == XOR) {
		std::cout << '^';
	} else if (opertype == EQ) {
		std::cout << "==";
	} else if (opertype == NEQ) {
		std::cout << "!=";
	} else if (opertype == LEQ) {
		std::cout << "<=";
	} else if (opertype == LT) {
		std::cout << "<";
	} else if (opertype == GEQ) {
		std::cout << ">=";
	} else if (opertype == GT) {
		std::cout << ">";
	} else if (opertype == SHL) {
		std::cout << "<<";
	} else if (opertype == SHR) {
		std::cout << ">>";
	}
}

Oper::Oper(std::string op) {
	if (op == "+") {
		opertype = PLUS;
	} else if (op == "-") {
		opertype = MINUS;
	} else if (op == "*") {
		opertype = MULT;
	} else if (op == "/") {
		opertype = DIV;
	} else if (op == "%") {
		opertype = MOD;
	} else if (op == "(") {
		opertype = LBRACKET;
	} else if (op == ")") {
		opertype = RBRACKET;
	} else if (op == "=") {
		opertype = ASSIGN;
	} else if (op == "&") {
		opertype = BITAND;
	} else if (op == "|") {
		opertype = BITOR;
	} else if (op == "^") {
		opertype = XOR;
	} else if (op == "==") {
		opertype = EQ;
	} else if (op == "!=") {
		opertype = NEQ;
	} else if (op == ">") {
		opertype = GT;
	} else if (op == "<") {
		opertype = LT;
	} else if (op == ">=") {
		opertype = GEQ;
	} else if (op == "<=") {
		opertype = LEQ;
	} else if (op == ">>") {
		opertype = SHR;
	} else if (op == "<<") {
		opertype = SHL;
	}
}

TYPE Oper::get_type(void) {
	if (opertype == PLUS || opertype == MINUS || opertype == MULT || 
		opertype == DIV || opertype == MOD || opertype == BITAND ||
		opertype == BITOR || opertype == XOR || opertype == EQ ||
		opertype == NEQ || opertype == LEQ || opertype == LT || 
		opertype == GEQ || opertype == GT || opertype == SHL || 
		opertype == SHL) {
		return EVALUATABLE_TYPE;
	}
	if (opertype == LBRACKET) {
		return LBRACKET_TYPE;
	}
	if (opertype == RBRACKET) {
		return RBRACKET_TYPE;
	}
	if (opertype == ASSIGN) {
		return ASSIGN_TYPE;
	}
	return NONE_TYPE;
}

int Oper::get_priority(void) {
	return PRIORITY[opertype];
}

void print_vector(std::vector <Lexem *> &v) {
	for(auto ptr: v) {
		ptr -> print();
		std::cout << "      |      ";
	}
	std::cout << std::endl;
}

std::map<std::string, int> varTable;

class Variable: public Lexem {
	int _value;
	std::string _name;
  public:
  	Variable();
  	Variable(std::string name);
  	Variable(std::string name, int value);
  	TYPE get_type();
  	void set_value(int value);
  	std::string get_name();
  	void print();
};

Variable::Variable() {}

Variable::Variable(std::string name) {
	_name = name;
}

Variable::Variable(std::string name, int value) {
	_name = name;
	_value = value;
}

TYPE Variable::get_type() {
	return VARIABLE_TYPE;
}

void Variable::set_value(int value) {
    _value = value;
    varTable[_name] = _value;
}

std::string Variable::get_name() {
	return _name;
}

void Variable::print() {
	std::cout << _name;
}

void print_var_table() {
    std::cout << "Variables Table:" << std::endl;
    for (std::map<std::string,int>::iterator it = varTable.begin(); it != varTable.end(); it++) {
        std::cout << it->first << " = " << it->second << std::endl;
    }
}

void print_stack(std::stack<Lexem *> & old_st) {
	std::stack<Lexem *> st = old_st;
	std::cout << "Stack: ";
	while (!st.empty()) {
		st.top()->print();
		st.pop();
	}
	std::cout << std::endl;
}

std::map<std::string, int> labelTable;

class Goto : public Oper {
	int _row;
  public:
  	Goto();
  	Goto(int);
  	Goto(const std::string &);
  	int get_row();
  	void print();
};

Goto::Goto() {}

Goto::Goto(int row) {
	_row = row;
}

Goto::Goto(const std::string &label) {
	_row = labelTable[label];
}

int Goto::get_row() {
	return _row;
}

void Goto::print() {}

bool is_white_space(char ch) {
	if (ch == ' ' || ch == '\t' || ch == '\n') {
		return true;
	}
	return false;
}

bool is_digit(char ch) {
	if (ch <= '9' && ch >= '0') {
		return true;
	}
	return false;
}

bool is_operation(std::string op) {
	if (op == "{" || op == "}" || op == "+" || op == "-" ||
		op == "*" || op == "%" || op == "/" || op == "(" ||
		op == ")" || op == "&" || op == "|" || op == "^" ||
		op == "==") {
		return true;
	}
	return false;
}

bool is_symbol(char ch) {
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_') {
		return true;
	}
	return false;
}

void make_number(std::vector<Lexem *> &infix, std::string &codeline, int & i) {
	std::string number = "";
	while (is_digit(codeline[i])) {
		number += codeline[i];
		++i;
	}
	--i;
	infix.push_back(new Number(stoi(number)));
}

void make_word(std::vector<Lexem *> &infix, std::string &codeline, int &i) {
	std::string word = "";
	while (is_symbol(codeline[i]) || is_digit(codeline[i])) {
		word += codeline[i];
		++i;
	}
	--i;
	infix.push_back(new Variable(word));
}

void make_goto(std::vector<Lexem *> &infix, std::string &codeline, int &i) {
	i += 4;
	std::string label = "";
	while (is_white_space(codeline[i])) {
		++i;
	}
	while (is_symbol(codeline[i]) || is_digit(codeline[i])) {
		label += codeline[i];
		++i;
	}
	--i;
	infix.push_back(new Goto(label));
}

std::string get_string(char ch) {
	std::string s(1, ch); 
	return s;   
} 

std::vector<Lexem *> parse_lexem(std::string codeline) {
	std::vector<Lexem *> infix;
	int len = codeline.size();
	std::string obj = "";
	for (int i = 0; i < len; ++i) {
		if (is_white_space(codeline[i])) {
			continue;
		} else if (is_digit(codeline[i])) {
			make_number(infix, codeline, i);
		} else if (is_operation(get_string(codeline[i]))) {
			infix.push_back(new Oper(get_string(codeline[i])));
		} else if (is_symbol(codeline[i])) {
			make_word(infix, codeline, i);
		} else if (codeline[i] == '=') {
			if (codeline[i + 1] == '=') {
				infix.push_back(new Oper("=="));
				++i;
			} else {
				infix.push_back(new Oper(get_string(codeline[i])));
			}
		} else if (codeline[i] == '!') {
			if (codeline[i + 1] == '=') {
				infix.push_back(new Oper("!="));
				++i;
			}
		} else if (codeline[i] == '<') {
			if (codeline[i + 1] == '=') {
				infix.push_back(new Oper("<="));
				++i;
			} else if (codeline[i + 1] == '<') {
				infix.push_back(new Oper("<<"));
				++i;
			} else {
				infix.push_back(new Oper(get_string(codeline[i])));
			}
		} else if (codeline[i] == '>') {
			if (codeline[i + 1] == '=') {
				infix.push_back(new Oper(">="));
				++i;
			} else if (codeline[i + 1] == '>') {
				infix.push_back(new Oper(">>"));
				++i;
			} else {
				infix.push_back(new Oper(get_string(codeline[i])));
			}
		}
	}
	return infix;
}

std::vector<Lexem *> build_postfix(std::vector<Lexem *> infix) {
	std::vector<Lexem *> postfix;
	std::stack<Lexem *> stack;
	int size = infix.size();
	for (int i = 0; i < size; i++) {
		if (infix[i] -> get_type() == NUMBER_TYPE) {
			postfix.push_back(infix[i]);
		} else if (infix[i] -> get_type() == VARIABLE_TYPE) {
			postfix.push_back(infix[i]);
		} else if(!stack.empty()) {
			if (infix[i] -> get_type() == LBRACKET_TYPE) {
				stack.push(infix[i]);
			} else if (infix[i] -> get_type() == RBRACKET_TYPE) {
				while (stack.top() -> get_type() != LBRACKET_TYPE) {
					postfix.push_back(stack.top());
					stack.pop();
				}
				stack.pop();
			} else if (infix[i] -> get_type() == ASSIGN_TYPE && stack.top() -> get_type() == ASSIGN_TYPE) {
				stack.push(infix[i]);
			} else if (stack.top() -> get_type() != LBRACKET_TYPE && ((Oper *)stack.top()) -> get_priority() >= ((Oper *)infix[i]) -> get_priority()) {
				while (!stack.empty() && stack.top() -> get_type() != LBRACKET_TYPE && ((Oper *)stack.top()) -> get_priority() >= ((Oper *)infix[i]) -> get_priority()) {
					postfix.push_back(stack.top());
					stack.pop();
				}	
				stack.push(infix[i]);
			} else {
				stack.push(infix[i]);
			}
		} else {
			stack.push(infix[i]);
		}
	}
	while (!stack.empty()) {
		postfix.push_back(stack.top());
		stack.pop();
	}
	return postfix;
}

Lexem *perform_evaluatable_operation(Lexem *leftValue, Lexem *rightValue, OPERATOR opertype) {
	Lexem *val; 
	int left = ((Number *)leftValue)->get_value();
	int right = ((Number *)rightValue)->get_value();
	if (opertype == PLUS) {
		val = new Number(left + right);
	} else if (opertype == MINUS) {
		val = new Number(left - right);
	} else if (opertype == MULT) {
		val = new Number(left * right);
	} else if (opertype == DIV) {
		val = new Number(left / right);
	} else if (opertype == MOD) {
		val = new Number(left % right);
	} else if (opertype == BITAND) {
		val = new Number(left & right);
	} else if (opertype == BITOR) {
		val = new Number(left | right);
	} else if (opertype == XOR) {
		val = new Number((left + right) % 2) ;
	} else if (opertype == EQ) {
		val = new Number(bool(left == right));
	} else if (opertype == NEQ) {
		val = new Number(bool(left != right));
	} else if (opertype == LEQ) {
        val = new Number(bool(left <= right));
    } else if (opertype == LT) {
        val = new Number(bool(left < right));
    } else if (opertype == GEQ) {
        val = new Number(bool(left >= right));
    } else if (opertype == GT) {
        val = new Number(bool(left > right));
    } else if (opertype == SHL) {
        val = new Number(left << right);
    } else if (opertype == SHR) {
        val = new Number(left >> right);
    }
	return val;
}

Lexem *perform_assign_operation(Lexem *left, Lexem *right) {
	Lexem *result;
	int number = ((Number *)right)->get_value();
	((Variable *)left)->set_value(number);
	result = new Number(number);
	return result;
}

int evaluate_postfix(std::vector<Lexem *> postfix) {
	Lexem *left, *right, *result;
	std::stack<Lexem *> stack;
	for (auto lexem: postfix) {
		if (lexem->get_type() == EVALUATABLE_TYPE) {
			right = stack.top();
			stack.pop();
			left = stack.top();
			stack.pop();
			result = perform_evaluatable_operation(left, right, ((Oper *)lexem)->get_oper_type());
			stack.push(result);
		} else if (lexem->get_type() == NUMBER_TYPE || lexem->get_type() == VARIABLE_TYPE) {
			stack.push(lexem);
		} else if (lexem->get_type() == ASSIGN_TYPE) {
			right = stack.top();
			stack.pop();
			left = stack.top();
			stack.pop();
			result = perform_assign_operation(left, right);
			stack.push(result);
		}
	}
	return ((Number *)stack.top())->get_value();
}

int main(void) {
	std::string codeline;
	std::vector<Lexem *> infix;
	std::vector<Lexem *> postfix;

	do {
		std::cout << "> ";
		getline(std::cin, codeline);
		infix = parse_lexem(codeline);
		postfix = build_postfix(infix);
		int value = evaluate_postfix(postfix);
		std::cout << ">>>> " << value << std::endl;
	} while (codeline != "quit");

	return 0;
}

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <stack>
#include <map>

#define DEBUG 1

	//************************
enum TYPE {
	NONE_TYPE,
	NUMBER_TYPE, 
	VARIABLE_TYPE,
 	OPERATION_TYPE, 
	LBRACKET_TYPE, 
	RBRACKET_TYPE,
	ASSIGN_TYPE
};

	//************************
class Lexem {
  public:
  	Lexem();
  	virtual void print() {}
  	virtual TYPE getType() = 0;
};

Lexem::Lexem() {}

class Number : public Lexem {
	int value;
  public:
  	Number();
  	Number(int);
  	int getValue();
  	void print();
  	TYPE getType();
};

	//************************
Number::Number() {
	if (DEBUG == 1) {
		std::cout << "Number default" << std::endl;
	}
}

Number::Number(int num) {
	value = num;
}

int Number::getValue() {
	return value;
}

void Number::print() {
	std::cout << value;
}

TYPE Number::getType() {
	return NUMBER_TYPE;
}

	//************************
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
	10 , 10 , 10
};

std::string OPERTEXT [] = {
	"(", ")",
	"=" ,
	"or" ,
	"and" ,
	"|",
	"^",
	"&",
	":==" , "!=" ,
	"<=" , "<" ,
	">=" , ">" ,
	"<<" , ">>" ,
	"+" , "-" ,
	"*", "/", "%"
};

class Oper : public Lexem {
	OPERATOR opertype;
  public:
  	Oper();
  	Oper(char);
  	TYPE getType();
  	void print();
  	int getPriority();
  	OPERATOR getOperType();
};

Oper::Oper() {
	if (DEBUG == 1) {
		std::cout << "oper def constr\n";
	}
}

OPERATOR Oper::getOperType() {
	return opertype;
}

void Oper::print() {
	if (opertype == PLUS) {
		std::cout << '+';
	}
	else if (opertype == MINUS) {
		std::cout << '-';
	}
	else if (opertype == LBRACKET) {
		std::cout << '(';
	}
	else if (opertype == RBRACKET) {
		std::cout << ')';
	}
	else if (opertype == MULT) {
		std::cout << '*';
	}
	else if (opertype == DIV) {
		std::cout << '/';
	}
	else if (opertype == MOD) {
		std::cout << '%';
	} else if (opertype == ASSIGN) {
		std::cout << '=';
	}
}

Oper::Oper(char ch) {
	if (ch == '+') {
		opertype = PLUS;
	} else if (ch == '-') {
		opertype = MINUS;
	} else if (ch == '*') {
		opertype = MULT;
	} else if (ch == '/') {
		opertype = DIV;
	} else if (ch == '%') {
		opertype = MOD;
	} else if (ch == '(') {
		opertype = LBRACKET;
	} else if (ch == ')') {
		opertype = RBRACKET;
	} else if (ch == '=') {
		opertype = ASSIGN;
	}
}

TYPE Oper::getType(void) {
	if (opertype == PLUS || opertype == MINUS ||
		opertype == MULT || opertype == DIV || opertype == MOD) {
		return OPERATION_TYPE;
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

int Oper::getPriority(void) {
	return PRIORITY[opertype];
}

	//****************************
std::map <std::string, int> VarTable;

class Variable : public Lexem {
	int value;
	std::string name;
  public:
  	Variable();
  	Variable(std::string);
  	void setValue(int);
  	void print();
  	TYPE getType();
};

Variable::Variable() {}

Variable::Variable(std::string input_name) {
	name = input_name;
}

void Variable::setValue(int newValue) {
    value = newValue;
    VarTable[name] = value;
}

void Variable::print() {
    std::cout << name;
}

TYPE Variable::getType() {
	return VARIABLE_TYPE;
}

	//*********************
void printVector(std::vector <Lexem *> &v) {
	std::cout << "Vector elements are : ";
	for(auto ptr: v) {
		ptr -> print();
	}
	std::cout << std::endl;
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

	//**********************
bool isoperation(char ch) {
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
		ch == '%' || ch == '(' || ch == ')') {
		return true;
	}
	return false;
}

bool isassign(char ch) {
	if (ch == '=') {
		return true;
	}
	return false;
}

bool ispass(char ch) {
	if (ch == ' ' || ch == '\t' || ch == '\n')
		return true;
	return false;
}

bool issymbol(char ch) {
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ||
		(ch >= 0 && ch <= 9)) 
		return true;
	return false;
}

	//************************
std::vector<Lexem *> parseLexem(std::string codeline) {
	std::vector<Lexem *> infix;
	codeline += ' ';
	int value = 0;

	for (long unsigned int i = 0; i < codeline.size();) {
		if (ispass(codeline[i])) {
			i++;
			continue;
		} else if (isoperation(codeline[i])) {
			infix.push_back(new Oper(codeline[i]));		
			i++;
		} else if (isdigit(codeline[i])) {
			value = 0;
			while (isdigit(codeline[i])) {
				value = value * 10 + codeline[i] - '0';
				i++;
			}
			infix.push_back(new Number(value));
			value = 0;
		} else if (isalpha(codeline[i])) {
			std::string name = "";
			while ((i < codeline.size()) && isalpha(codeline[i])) {
				if (codeline[i] == ' ' || codeline[i] == '\t') {
					break;
				}
				name += codeline[i];
				i++;
			}
			infix.push_back(new Variable(name));
		} else if (isassign(codeline[i])) {
			std::cout << "IT IS ASSIGN!!!!" << std::endl; 
			infix.push_back(new Oper(codeline[i]));
			i++;
		}
	}
	
	if (DEBUG == 1) {
		std::cout << "INFIX:     ";
		printVector(infix);
	}
	
	return infix;
}

	//***********************
std::vector<Lexem *> builtPostfix (std::vector<Lexem *> infix) {
	std::vector<Lexem *> postfix;
	std::stack <Lexem *> stack;
	
	for (auto lexem: infix) {
		if (lexem -> getType() == NUMBER_TYPE  || lexem -> getType() == VARIABLE_TYPE) {
			postfix.push_back(lexem);
		} else if (!stack.empty()) {
			if (((Oper *)lexem)->getPriority() == LBRACKET) {
				stack.push(lexem);
			} else if (((Oper *)lexem)->getPriority() == RBRACKET) {
				while (stack.top()->getType() != LBRACKET_TYPE) {
					postfix.push_back(stack.top());
					stack.pop();
				}
				stack.pop();
			} else if (stack.top()->getType() != LBRACKET_TYPE && ((Oper *)stack.top())->getPriority() >= ((Oper *)lexem)->getPriority()) {
				while (!stack.empty() && stack.top()->getType() != LBRACKET_TYPE && ((Oper *)stack.top())->getPriority() >= ((Oper *)lexem)->getPriority()) {
					postfix.push_back(stack.top());
					stack.pop();
				}
				//stack.push(lexem); //RBRACKET delete
			} else if (lexem -> getType() == ASSIGN_TYPE && stack.top() -> getType() == ASSIGN_TYPE) {
				stack.push(lexem);
			} else {
				stack.push(lexem); 
			}
		} else {
			stack.push(lexem);
		}
	}
	while (!stack.empty()) {
		postfix.push_back(stack.top());
		stack.pop();
	}

	if (DEBUG == 1) {	
		std::cout << "POSTFIX:  ";
		printVector(postfix);
		print_stack(stack);	
	}

	return postfix;
} 

	//*********************
Lexem *performOperation(Lexem *leftValue, Lexem *rightValue, OPERATOR opertype) {
	Lexem *val; 
	int leftNumber = ((Number *)leftValue)->getValue();
	int rightNumber = ((Number *)rightValue)->getValue();
	if (opertype == PLUS) {
		val = new Number(leftNumber + rightNumber);
	} else if (opertype == MINUS) {
		val = new Number(leftNumber - rightNumber);
	} else if (opertype == MULT) {
		val = new Number(leftNumber * rightNumber);
	} else if (opertype == DIV) {
		val = new Number(leftNumber / rightNumber);
	} else if (opertype == MOD) {
		val = new Number(leftNumber % rightNumber);
	} else if (opertype == XOR) {
		val = new Number(leftNumber ^ rightNumber);
	} else if (opertype == BITAND) {
		val = new Number(leftNumber & rightNumber);
	} else if (opertype == BITOR) {
		val = new Number(leftNumber | rightNumber);
	} else if (opertype == ASSIGN) {
        ((Variable *)leftValue)->setValue(((Number *)rightValue)->getValue());
        val = new Number(((Number *)rightValue)->getValue());
	}
	return val;
}

int evaluatePostfix(std::vector<Lexem *> postfix) {
	Lexem *left, *right, *result;
	std::stack<Lexem *> stack;

	for (auto lexem: postfix) {
		if (lexem->getType() == OPERATION_TYPE) {
			right = stack.top();
			stack.pop();
			left = stack.top();
			stack.pop();
			result = performOperation(left, right, ((Oper *)lexem)->getOperType());
			stack.push(result);
		} else if (lexem->getType() == NUMBER_TYPE) {
			stack.push(lexem);
		} else {
			//std::cout << result << std::endl;
		}
	}
	return ((Number *)stack.top())->getValue();
}

	//*********************
int main(void) {
	std::string codeline;
	std::vector<Lexem *> infix;
	std::vector<Lexem *> postfix;

	std::getline(std::cin, codeline);
	infix = parseLexem(codeline);
	postfix = builtPostfix(infix);
	int value = evaluatePostfix(postfix);
	std::cout << "value: " << value << std::endl;
	return 0;
}

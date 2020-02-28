#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <stack>
#include <map>

#define DEBUG 1

std::map<std::string, Variable *> varTable;

enum TYPE {
	NONE_TYPE,
	NUMBER_TYPE, 
	VARIABLE_TYPE, 
	OPERATION_TYPE, 
	LBRACKET_TYPE, 
	RBRACKET_TYPE
};

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
	" := " ,
	" or " ,
	" and " ,
	"|",
	"^",
	"&",
	" == " , " != " ,
	" <= " , " <" ,
	" >= " , " >" ,
	" <<" , " >>" ,
	" + " , " -" ,
	"*", "/", "%"
};

class Oper : public Lexem {
	OPERATOR opertype;
  public:
  	Oper();
  	Oper(char);
  	TYPE getType();
  	int getPriority();
  	void print();
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

Oper::Oper(char ch) {
	if (ch == '+') {
		opertype = PLUS;
	}
	else if (ch == '-') {
		opertype = MINUS;
	}
	else if (ch == '*') {
		opertype = MULT;
	}
	else if (ch == '/') {
		opertype = DIV;
	}
	else if (ch == '%') {
		opertype = MOD;
	}
	else if (ch == '(') {
		opertype = LBRACKET;
	}
	else if (ch == ')') {
		opertype = RBRACKET;
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
	return NONE_TYPE;
}

int Oper::getPriority(void) {
	return PRIORITY[opertype];
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
	}
}

class Variable : public Lexem {
	int value;
	std::string name;
  public:
  	Variable();
  	Variable(std::string name);
  	Variable(std::string name, int value);
  	//void print();
  	TYPE getType();
};

Variable::Variable() {}

Variable::Variable(std::string input_name) {
	name = input_name;
}

Variable::Variable(std::string input_name, int input_value) {
	value = input_value;
	name = input_name;
}

TYPE Variable::getType() {
	return VARIABLE_TYPE;
}

void printVector(std::vector <Lexem *> &v) {
	std::cout << "The infix vector elements are : ";
	for(auto ptr: v) {
		ptr -> print();
	}
	std::cout << std::endl;
}

bool isoperation(char ch) {
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
		ch == '%' || ch == '(' || ch == ')') {
		return true;
	}
	return false;
}

bool isassign(char ch) {
	if (ch == ':') {
		return true;
	}
	return false;
}

std::vector<Lexem *> parseLexem(std::string codeline) {
	std::vector<Lexem *> infix;
	codeline += ' ';
	int value = 0;
	for (long unsigned int i = 0; i < codeline.size();) {
		if (codeline[i] == ' ' || codeline[i] == '\t' || codeline[i] == '\n') {
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
		} else if (isassign(codeline[i])) {

		}
	}
	if (DEBUG == 1) {
		printVector(infix);
	}
	return infix;
}

void print_stack(std::stack<Lexem *> & old_st)
{
	std::stack<Lexem *> st = old_st;
	std::cout << "Stack: ";
	while (!st.empty()) {
		st.top()->print();
		st.pop();
	}
	std::cout << std::endl;
}

std::vector<Lexem *> builtPostfix (std::vector<Lexem *> infix) {
	std::vector<Lexem *> postfix;
	std::stack <Lexem *> stack;
	
	for (auto lexem: infix) {
		if (lexem -> getType() == NUMBER_TYPE) {
			postfix.push_back(lexem);
		} else if (!stack.empty()) {
			if (((Oper *)lexem)->getPriority() == LBRACKET) {
				stack.push(lexem);
			} else if (((Oper *)lexem)->getPriority() == RBRACKET) {
				while (stack.top()->getType() != LBRACKET_TYPE) {
					postfix.push_back(stack.top());
					stack.pop();
					stack.pop(); //lBRACKET add
				}
				stack.pop();
			} else if (stack.top()->getType() != LBRACKET_TYPE && ((Oper *)stack.top())->getPriority() >= ((Oper *)lexem)->getPriority()) {
				while (!stack.empty() && stack.top()->getType() != LBRACKET_TYPE && ((Oper *)stack.top())->getPriority() >= ((Oper *)lexem)->getPriority()) {
					postfix.push_back(stack.top());
					stack.pop();
				}
				//stack.push(lexem); //RBRACKET delete
			} else {
				stack.push(lexem); 
			}
		} else {
			stack.push(lexem);
		}
	}
	//print_stack(stack);	
	while (!stack.empty()) {
		postfix.push_back(stack.top());
		stack.pop();
	}
	if (DEBUG == 1) {	
		printVector(postfix);
		print_stack(stack);	
	}
	return postfix;
} 

int performOperation(int leftNumber, int rightNumber, OPERATOR opertype) {
	int val; 
	if (opertype == PLUS) {
		val = leftNumber + rightNumber;
	} else if (opertype == MINUS) {
		val = leftNumber - rightNumber;
	} else if (opertype == MULT) {
		val = leftNumber * rightNumber;
	} else if (opertype == DIV) {
		val = leftNumber * rightNumber;
	} else if (opertype == MOD) {
		val = leftNumber * rightNumber;
	} else {
		exit(0);		//потом убрать при дополнии
	}
	return val;
}

int evaluatePostfix(std::vector<Lexem *> postfix) {
	Lexem *left, *right;
	int result;
	std::stack<Lexem *> stack;

	for (auto lexem: postfix) {
		if (lexem->getType() == OPERATION_TYPE) {
			right = stack.top();
			stack.pop();
			left = stack.top();
			stack.pop();
			result = performOperation(((Number *)left)->getValue(), ((Number *)right)->getValue(), ((Oper *)lexem)->getOperType());
			stack.push((Lexem *) (new Number(result)));
		} else if (lexem->getType() == NUMBER_TYPE) {
			stack.push(lexem);
		} else {
			std::cout << result << std::endl;
		}
	}
	return ((Number *)stack.top())->getValue();
}

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
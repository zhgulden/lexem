#ifndef LEXEM_H
#define LEXEM_H

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <stack>
#include <map>

enum TYPE {
	NONE_TYPE,
	NUMBER_TYPE, 
	VARIABLE_TYPE,
 	EVALUATABLE_TYPE, 
	LBRACKET_TYPE, 
	RBRACKET_TYPE,
	ASSIGN_TYPE
};

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

class Lexem {
  public:
  	Lexem();
  	virtual void print() {}
  	virtual TYPE get_type() = 0;
};

class Number : public Lexem {
	int value;
  public:
  	Number();
  	Number(int);
  	int get_value();
  	void print();
  	TYPE get_type();
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

class Goto : public Oper {
	int _row;
  public:
  	Goto();
  	Goto(int);
  	Goto(const std::string &);
  	int get_row();
  	void print();
};

void print_vector(std::vector <Lexem *> &v);
void print_var_table();
void print_stack(std::stack<Lexem *> & old_st);

bool is_white_space(char ch);
bool is_digit(char ch);
bool is_operation(std::string op);
bool is_symbol(char ch);

void make_number(std::vector<Lexem *> &infix, std::string &codeline, int & i);
void make_word(std::vector<Lexem *> &infix, std::string &codeline, int &i);
void make_goto(std::vector<Lexem *> &infix, std::string &codeline, int &i);

std::string get_string(char ch);

std::vector<Lexem *> parse_lexem(std::string codeline);
std::vector<Lexem *> build_postfix(std::vector<Lexem *> infix);
Lexem *perform_evaluatable_operation(Lexem *leftValue, Lexem *rightValue, OPERATOR opertype);
Lexem *perform_assign_operation(Lexem *left, Lexem *right);
int evaluate_postfix(std::vector<Lexem *> postfix);

#endif

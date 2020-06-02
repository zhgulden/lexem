#include <lexem.hpp>

int main(void) {
	std::string codeline;
	std::vector<Lexem *> infix;
	std::vector<Lexem *> postfix;

	do {
		std::cout << "> ";
		getline(std::cin, codeline);
		infix = parse_lexem(codeline);
		// std::cout << "INFIX:" << std::endl;
		//print_vector(infix);
		postfix = build_postfix(infix);
		//std::cout << "POSTFIX:" << std::endl;
		//print_vector(postfix);
		int value = evaluate_postfix(postfix);
		std::cout << ">>>> " << value << std::endl;
	} while (codeline != "quit");
	return 0;
}
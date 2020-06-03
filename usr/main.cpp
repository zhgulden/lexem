#include <lexem.hpp>

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

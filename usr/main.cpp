#include <lexem.hpp>

int main(void) {
	std::vector<Lexem *> infix;
    std::string codeline;
    std::vector<PREFIXTYPE> prefix_vector;
    std::vector<std::vector<Lexem *>> infix_lines, postfix_lines;
    for (unsigned r = 0; std::getline(std::cin, codeline); r++) {
        if (codeline == "exit")
            break;
        prefix_vector.push_back(get_prefix_type(codeline));
        infix = parse_lexem(codeline);
        infix_lines.push_back(infix);
    }
    fill_label_map(prefix_vector);
    for (unsigned r = 0; r < infix_lines.size(); r++)
        postfix_lines.push_back(build_postfix(infix_lines[r]));
    exec_code(postfix_lines, prefix_vector);
    print_vars();
	return 0;
}

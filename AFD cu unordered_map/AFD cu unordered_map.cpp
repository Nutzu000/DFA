#include <iostream>
#include "AFD.h"
#include <unordered_map>
int main()
{
	AFD a;
	a.citireFisier("Input.txt");
	std::cout << a;
	if (a.verifica()) {
		std::string input;
		std::cout << "Va puteti opri cu semnul \"!\"\n";
		do {
			std::cout << "Introduceti un cuvant: ";
			std::cin >> input;
			if (input != "!") {
				std::cout << a.accepta(input) << std::endl;
			}
		} while (input != "!");
	}
	else {
		std::cout << "AFD-ul este gresit!\n";
	}
}

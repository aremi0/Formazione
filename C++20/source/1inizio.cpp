/*
	@file progetto-prova
	@author aremi
	@version 0.1
	@date 2022-08-06

	1. moduli C++20 ed utilizzo, puntatori a costanti, ranged for-loop
*/

#pragma once
import <iostream>;
import <numbers>;
import <cctype>;
import <cstdio>;
import <cstdlib>;
import <vector>;
import <array>;
import <thread>;
import <chrono>;
import <map>;
import <string>;
import <random>;

int main(int argc, char* argv[]) {
	auto vabiabile{ 25.3 };
	FILE* f;

	std::cout << "variabile 'auto' " << vabiabile << std::endl;
	std::cout << "pi " << std::numbers::pi << std::endl;

	std::printf("mi trovo meglio con questo mi sa... %d\n", static_cast<int>(vabiabile));

	std::cout << "Inserisci un valore\n";
	std::cin >> vabiabile;
	if(isdigit(vabiabile))
		printf("bra\n");
	else
		printf("e no\n");

	fopen_s(&f, "./output.txt", "w");

	if(!f) {
		perror("fopen");
		exit(1);
	}

	fputs("aellaaaaa", f);



	const int vettore[] = { 5, 9, 10, 36, 25 };

	std::cout << std::size(vettore) << std::endl;

	const char* pstars[]{
		"Fatty Arbuckle", "Clara Bow", "Lassie",
		"Slim Pickens", "Boris Karloff", "Mae West",
		"Oliver Hardy", "Greta Garbo"
	};

	pstars[5] = pstars[6];

	for(auto x : pstars)
		std::cout << x << std::endl;

	return 0;
}
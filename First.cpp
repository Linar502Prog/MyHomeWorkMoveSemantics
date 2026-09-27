#include<iostream>
#include<vector>
template<typename T>
void move_vectors(T& one, T& two) {
	two = std::move(one);
}

int main() {
	std::vector<std::string> one = { "test_string1","test_string2" };
	std::vector<std::string> two;
	move_vectors(one,two);

	for (size_t i = 0; i < two.size(); i++) {
		std::cout << two[i] << std::endl;
	}
	return EXIT_SUCCESS;
}
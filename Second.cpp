#include<iostream>
#include<vector>
#include<algorithm>
class big_integer {
	std::string m_number;
public:
	big_integer(const std::string& number) {
		m_number = number;
	}
	big_integer(big_integer&& other) {
		m_number = std::move(other.m_number);
	}
	big_integer operator+(const big_integer& other) {
		std::string plus_res;
		int carry = 0;
		for (int i{ static_cast<int>(m_number.size())-1 },j{ static_cast<int>(other.m_number.size())-1 }; i >= 0 || j >= 0; i--, j--) {
			if (i < 0) {
				int b = static_cast<int>(other.m_number[j] - '0');
				if ((b + carry) >= 10) {
					plus_res.push_back((b + carry)%10 + '0');
					carry = (b + carry) / 10;
				}
				else {
					plus_res.push_back(b + carry + '0');
				}

			}
			else if (j < 0) {
				int a = static_cast<int>(m_number[i] - '0');
				if ((a + carry) >= 10) {
					plus_res.push_back((a + carry) % 10 + '0');
					carry = (a + carry) / 10;
				}
				else {
					plus_res.push_back(a + carry + '0');
				}
			}
			else {
				int a = static_cast<int>(m_number[i] - '0');
				int b = static_cast<int>(other.m_number[j] - '0');
				int sum = a + b + carry;
				if (sum < 10) {
					plus_res.push_back(sum + '0');
					carry = 0;
				}
				else {
					int rest = (sum) % 10;
					plus_res.push_back(rest + '0');
					carry = sum / 10;
				}
			}
		}
		if (carry != 0) {
			plus_res.push_back(carry + '0');
		}
		std::reverse(plus_res.begin(),plus_res.end());
		return big_integer(plus_res);
	}
	friend std::ostream& operator<<(std::ostream& os, const big_integer& other);
	big_integer& operator=(big_integer&& other) {
		m_number = std::move(other.m_number);
		return *this;
	}
	big_integer operator*(int multiplier) {
		std::string mult_res;
		int carry{ 0 }, sum{ 0 };
		for (int i = static_cast<int>(m_number.size()) - 1; i >= 0; i--) {
			sum = (m_number[i] - '0') * multiplier + carry;
			mult_res.push_back(sum % 10 + '0');
			carry = sum / 10;
		}
		if (carry > 0) {
			mult_res.push_back(carry + '0');
		}
		std::reverse(mult_res.begin(), mult_res.end());
		return big_integer(mult_res);
	}
};
std::ostream& operator<<(std::ostream& os, const big_integer& other) {
	return os << other.m_number;
}



int main() {

	auto number1 = big_integer("114575");
	auto number2 = big_integer("78524");
	auto result = number1 + number2;
	auto result1 = number1 * 3;
	std::cout << result << std::endl; // 193099
	std::cout << result1;

	return EXIT_SUCCESS;
}
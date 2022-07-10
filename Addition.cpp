
#include <iostream>
#include <cstring>
using namespace std;

struct BigNumber {
	int numbers[1000] = {0};
	int length = 0;

	void transfer(char str[]) {

		length = strlen(str);
		memset(numbers, 0, sizeof(numbers));
		for (int i = 0; i < length; i++) {
			numbers[length - 1 - i] = str[i] - 48;
		}
	}
	void print() {
		for (int i = length; i > 0; i--) {
			cout << numbers[i-1];
		}
	}
	void leftShift(int left) {
		for (int i = length - 1; i >= 0; i--) {
			numbers[i + left] = numbers[i];
		}
		for (int j = 0; j < left; j++) {
			numbers[j] = 0;
		}
		length += left;
	}

	static void add(const BigNumber& a, const BigNumber& b, BigNumber& result) {
		int i = 0;

		i = 0;
		while (i < max(a.length, b.length)) {
			result.numbers[i] = a.numbers[i] + b.numbers[i];
			i++;
		}
		i = 0;
		result.length = max(a.length, b.length);
		for (int j = 0; j < max(a.length, b.length); j++) {
			if (result.numbers[j] >= 10) {
				result.numbers[j + 1] += 1;
				result.numbers[j] %= 10;
				if (j == max(a.length, b.length) - 1) {
					result.length = max(a.length, b.length) + 1;
				}
			}
		}
	}

	static void multiplyOne(const BigNumber& a, int number, BigNumber& result) {
		for (int i = 0; i < a.length; i++) {
			result.numbers[i] = a.numbers[i] * number;

		}
		result.length = a.length;
		for (int j = 0; j < a.length; j++) {
			if (result.numbers[j] >= 10) {
				result.numbers[j + 1] += result.numbers[j] / 10;
				result.numbers[j] %= 10;
				if (j == a.length - 1) {
					result.length = a.length + 1;
				}

			}
		}
	}

	static void multiply(const BigNumber& a, const BigNumber& b, BigNumber& result) {
		BigNumber mediator;
		BigNumber carrier;
		for (int i = 0; i < b.length; i++) {
			memset(&mediator, 0, sizeof(mediator));
			multiplyOne(a, b.numbers[i], mediator);
			mediator.leftShift(i);
			memset(&carrier, 0, sizeof(carrier));
			add(result, mediator, carrier);
			result = carrier;
		}
	}

};

int main() {
	BigNumber a;
	BigNumber b;
	BigNumber result;
	char str[1000];
	cin >> str;
	a.transfer(str);
	cin >> str;
	b.transfer(str);
	BigNumber::multiply(a, b, result);
	result.print();
}
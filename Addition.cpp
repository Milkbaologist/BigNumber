// Addition.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <cstring>
using namespace std;

struct BigNumber {
	/*char str[1000] = {0};*/
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
	//cout << strtof(a.str, NULL) * strtof(b.str, NULL) << endl;
	result.print();
}



// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: i
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

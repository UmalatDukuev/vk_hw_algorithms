/*Подсчитать кол-во единичных бит в входном числе , стоящих на четных позициях.
Позиции битов нумеруются с 0.

Необходимо использование битовых операций.
Использование арифметических операций запрещено.
*/

#include <iostream>

int NumOfEven(int digit){
	int count = 0;
	for (int i = 0; i<32; i+=2){
		if ((digit >> i)&1 == 1){
			count++;
		}
	}
	return count;
}
int main(){
	int p;
	std::cin >> p;
	std::cout << NumOfEven(p)<< std::endl;
	return 0;
}

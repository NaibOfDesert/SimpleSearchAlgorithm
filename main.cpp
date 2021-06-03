#include <iostream>
#include <stdio.h>
#include <inttypes.h>

using namespace std;

// struktura danej sekty
struct cult_member
{
	long long int number;
	cult_member* next;
};

void push(cult_member*& _head, long long int _number) {
	cult_member* person = new cult_member;

	person->number = _number;
	if (_head) { // == true
		person->next = _head->next;
		_head->next = person;
	}
	else person->next = person;
	_head = person; // ustawianie head - ostatniego elementu
}

long long int pop(cult_member*& _present, cult_member*& _back) { // wskazac numer usuwanego elementu
	long long int number{};
	cult_member* person = new cult_member;
	if (_present) { // == true
		person = _present;
		// ustawiamy numer
		number = _present->number;
		// zmieniamy adres
		_back->next = _present->next;
		_present = _back->next;
	}
	// zwalnianie pamieci
	delete person;
	return number;
}

void pop_final(cult_member*& _present) { // wskazac numer usuwanego elementu
	if (_present) { // == true
		if (_present->next != nullptr) {
			cult_member* person = new cult_member;
			person = _present;
			// ustawiamy numer
			_present = _present->next;
			delete person;
		}
		else delete _present;
	}
}


int main() {
	std::ios::sync_with_stdio(false);
	unsigned int count;
	long long int quantity;
	long long int number;
	// wczytywanie iloœci sekt
	scanf_s(" %u", &count);
	long long int* list = new long long int[count];
	// wczytywanie danych poszczególnych sekt
	for (unsigned int i = 0; i < count; i++) {
		scanf_s(" %lld", &quantity);
		scanf_s(" %lld", &number);
		if (number < 0) {
			number = quantity + number + 1;
		}
		if (quantity == 0) {
			list[i] = 0;
		}
		if (quantity == 1) {
			list[i] = 1;
		}
		if (quantity > 1) {
			cult_member* head = nullptr;
			for (long long int j = 1; j < quantity + 1; j++) {
				push(head, j);
			}
			long long int counter = 0;
			long long int result = 0;
			cult_member* present = head->next;
			cult_member* back = head;
			int counter_to_two = 0;
			while (counter < number) {
				counter_to_two++;
				if (counter_to_two == 1) {
					back = present;
					present = present->next;
				}
				if (counter_to_two == 2) {
					counter_to_two = 0;
					result = pop(present, back);
					counter++;
				}
			}
			list[i] = result;
			do {
				pop_final(present);
			} while (present == nullptr);
		}
	}
	for (unsigned int i = 0; i < count; i++) {
		printf_s("%lld \n", list[i]);
	}
	delete[] list;
	return 0;
}

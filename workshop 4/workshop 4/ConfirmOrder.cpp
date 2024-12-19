#include <iostream>
#include <algorithm>
#include "ConfirmOrder.h"
#include "Toy.h"
using namespace seneca;

namespace seneca {
	void ConfirmOrder::resize(size_t newCapacity) {
		const Toy** temp = new const Toy * [newCapacity];
		for (size_t i = 0; i < size; i++) {
			temp[i] = toys[i];
		}
		delete[] toys;
		toys = temp;
		capacity = newCapacity;
	}

	ConfirmOrder& ConfirmOrder::operator+=(const Toy& toy)
	{
		
		for (size_t i = 0; i < size; i++) {
			if (toys[i] == &toy) {
				return *this;
			}
		}
		if (size >= capacity) {
			resize(capacity == 0 ? 1 : capacity * 2);
		}
		toys[size++] = &toy;
		return *this;

	}

	ConfirmOrder& ConfirmOrder::operator-=(const Toy& toy)
	{
		
		for (size_t i = 0; i < size; i++)
		{
			if (toys[i] == &toy) {
				toys[i] = nullptr;
			}
		}

		return *this;
	}

	ConfirmOrder::~ConfirmOrder(){}

	ostream& operator<<(ostream& os, const ConfirmOrder& co)
	{

		os << "--------------------------" << endl;
		os << "Confirmations to Send" << endl;
		os << "--------------------------" << endl;

		if (co.size == 0) {
			os << "There are no confirmations to send!" << endl;
		}
		else {
			for (size_t i = 0; i < co.size; i++)
			{
				if (co.toys[i] != nullptr) {
					os << *co.toys[i];
				}
			}
		}
		os << "--------------------------" << endl;
		return os;
	}

}


#ifndef SENECA_CONFRIMORDER_H
#define SENECA_CONFRIMORDER_H
#include "Toy.h"


namespace seneca {
	class ConfirmOrder  {
		const Toy** toys;
		size_t capacity;
		size_t size;

		void resize(size_t newCapacity);

	public:
		ConfirmOrder() :toys(nullptr), capacity(0), size(0) {};
		ConfirmOrder& operator+=(const Toy& toy);
		ConfirmOrder& operator-=(const Toy& toy);
		~ConfirmOrder();
		friend std::ostream& operator << (std::ostream& os, const ConfirmOrder& co);
	};
}
#endif // !SENECA_CONFRIMORDER_H


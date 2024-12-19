#include <memory>
#include "list.h"
#include "element.h"
#include "utilities.h"

using namespace std;

namespace seneca {
	List<Product> mergeRaw(const List<Description>& desc, const List<Price>& price) {
		List<Product> priceList;
		// TODO: Add your code here to build a list of products
		//         using raw pointers

        for (size_t i = 0; i < desc.size(); ++i) {
            for (size_t j = 0; j < price.size(); ++j) {
                if (desc[i].code == price[j].code) {
                    std::unique_ptr<Product> p = std::make_unique<Product>(desc[i].desc, price[j].price);
                    p->validate();
                    priceList += std::move(p); 
                }
            }
        }

        return priceList;

	
	}
    List<Product> mergeSmart(const List<Description>& descriptions, const List<Price>& prices)
    {
        List<Product> mergedList;
        for (size_t i = 0; i < descriptions.size() && i < prices.size(); ++i) {
            for (size_t j = 0; j < prices.size(); ++j) {
                if (descriptions[i].code == prices[j].code) {
                    std::unique_ptr<Product> p = std::make_unique<Product>(descriptions[i].desc, prices[j].price);
                    p->validate();
                    mergedList += std::move(p);
                }
            }
        }
        return mergedList;
    
}

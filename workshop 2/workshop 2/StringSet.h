#ifndef SENECA_STRINGSET_H
#define SENECA_STRINGSET_H

namespace seneca {

	class StringSet {
		std::string* strings;
		size_t numOfStrings;

	public:
		StringSet();
		StringSet(const char* filename);
		StringSet(const StringSet& ss); 
		StringSet& operator=(const StringSet& ss);
		~StringSet(); 
		size_t size() const;
		std::string operator[](size_t index) const;
		 StringSet(StringSet&& ss) noexcept;   // move assignment 
		StringSet& operator=(StringSet&& ss) noexcept; 	// move constructor 
	};
}

#endif

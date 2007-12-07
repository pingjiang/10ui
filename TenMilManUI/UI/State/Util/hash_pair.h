#ifndef HASH_PAIR_H_
#define HASH_PAIR_H_

#include <functional>
#include <map>
#include <string>

#include <tr1/unordered_map>
#include <tr1/memory>

using std::pair;
using std::string;
using std::unary_function;

using std::tr1::hash;
using std::tr1::shared_ptr;

template<class TC>
struct hash_pair : public unary_function< const pair<TC, TC>&, size_t> {
	size_t operator()(const pair<TC,TC>& val) const{
		hash<string> functor = hash<string>(); 
		size_t seed = functor(val.first);
		seed =  functor(val.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		return seed;
	}
};

#endif /*HASH_PAIR_H_*/

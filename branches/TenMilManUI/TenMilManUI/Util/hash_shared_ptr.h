#ifndef HASH_SHARED_PTR_H_
#define HASH_SHARED_PTR_H_

#include <functional>
#include <tr1/memory>

using std::unary_function;
using std::tr1::shared_ptr;

template<class TC>
struct hash_shared_ptr : public unary_function< const shared_ptr<TC>&, size_t> {
	size_t operator()(const shared_ptr<TC>& val) const{
		return (size_t) val.get();
	}
};

#endif /*HASH_SHARED_PTR_H_*/

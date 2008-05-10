#ifndef HASH_SHARED_PTR_H_
#define HASH_SHARED_PTR_H_

#include <functional>
#include <TenMilManUI/Util/SmartPointer.h>

using std::unary_function;

template<class TC>
struct hash_shared_ptr : public unary_function< const sp<TC>&, size_t> {
	size_t operator()(const sp<TC>& val) const{
		return (size_t) val.get();
	}
};

#endif /*HASH_SHARED_PTR_H_*/

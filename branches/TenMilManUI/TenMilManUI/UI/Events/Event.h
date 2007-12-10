#ifndef EVENT_H_
#define EVENT_H_

#include <string>
using std::string;

namespace TenUI {

	class Event {
	protected:
		string type;
		
	public:
		Event(string _type);
		virtual ~Event();
		
		const string& getType();
	};

}

#endif /*EVENT_H_*/

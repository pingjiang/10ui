#ifndef EVENT_H_
#define EVENT_H_

#include <string>
using std::string;

namespace TenUI {

	class Event {
	private:
		string type;
		
	public:
		Event(string _type);
		virtual ~Event();
		
		const string& getType(){
			return type;
		}
	};

}

#endif /*EVENT_H_*/

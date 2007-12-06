#ifndef HORIZONTALALIGNSTYLEDATA_H_
#define HORIZONTALALIGNSTYLEDATA_H_

#include <string>
#include <tr1/unordered_set>

#include "EnumStyleData.h"

using namespace std;
using namespace std::tr1;

namespace TenUI {
	
	namespace HorizontalAlignStyleOptions {
		string LEFT = "sdf";
		string CENTER = "sdf";
		string RIGHT = "sdf";
	}

	class HorizontalAlignStyleData : public EnumStyleData {
	private: 
		void init(){
			enumSet.insert(HorizontalAlignStyleOptions::LEFT);
			enumSet.insert(HorizontalAlignStyleOptions::CENTER);
			enumSet.insert(HorizontalAlignStyleOptions::RIGHT);
			defaultValue = value = HorizontalAlignStyleOptions::LEFT;
		}
		
	public:
		HorizontalAlignStyleData(){
			init();
		}
		HorizontalAlignStyleData(const unordered_set< string, hash<string> >& eset, const string& def)
			:EnumStyleData(){
			init();
		}
		virtual ~HorizontalAlignStyleData(){}
	};

}

#endif /*HORIZONTALALIGNSTYLEDATA_H_*/

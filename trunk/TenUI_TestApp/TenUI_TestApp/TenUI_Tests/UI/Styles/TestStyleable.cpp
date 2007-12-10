#include "TestStyleable.h"

namespace TenUI{

	TestStyleable::TestStyleable(){
		// initStyles() would normally be called by UIComponent's init() method
		initStyles();
	}
	
	/***********************************/
	/*        Stylable Overrides       */
	/***********************************/
	void TestStyleable::initStyles(){
		ColorStyleData* color1_style = new ColorStyleData();
		ColorStyleData* color2_style = new ColorStyleData();
		
		IntStyleData* 	int1_style = new IntStyleData();
		IntStyleData* 	int2_style = new IntStyleData();
		
		FloatStyleData* float1_style = new FloatStyleData();
		FloatStyleData* float2_style = new FloatStyleData();
		
		EnumStyleData* 	enum1_style = new EnumStyleData();
		EnumStyleData* 	enum2_style = new EnumStyleData();;
	}
}
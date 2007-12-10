#ifndef TESTSTYLEABLE_H_
#define TESTSTYLEABLE_H_

#include <TenMilManUI/UI/Styles/Styleable.h>

namespace TenUI{

	class TestStyleable : public Styleable {
	protected:
		ColorStyleData* color1_style;
		ColorStyleData* color2_style;
		
		IntStyleData* 	int1_style;
		IntStyleData* 	int2_style;
		
		FloatStyleData* float1_style;
		FloatStyleData* float2_style;
		
		EnumStyleData* 	enum1_style;
		EnumStyleData* 	enum2_style;		
		
	public:
		TestStyleable();
		
		/***********************************/
		/*        Stylable Overrides       */
		/***********************************/
		virtual void initStyles();
	};

}

#endif /*TESTSTYLEABLE_H_*/

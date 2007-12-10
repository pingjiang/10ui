#include "StyleTest_App.h"

#include <TenMilManUI/TenUI_Globals.h>

#include <TenMilManUI/Graphics/Util/ColorHex.h>

#include <TenMilManUI/UI/Styles/Styleable.h>

#include <TenMilManUI/UI/Styles/SingleStyle.h>
#include <TenMilManUI/UI/Styles/ArrayStyle.h>

#include <TenMilManUI/UI/Styles/StyleData/ColorStyleData.h>
#include <TenMilManUI/UI/Styles/StyleData/IntStyleData.h>
#include <TenMilManUI/UI/Styles/StyleData/FloatStyleData.h>
#include <TenMilManUI/UI/Styles/StyleData/StringStyleData.h>

namespace TenUI {
	StyleTest_App::StyleTest_App(){}

	template<class StyleDataType> 
	bool StyleTest_App::test_ParseData_ToString(StyleDataType* styleData, const string& parseableString, const string& toStringResult){
		styleData->parseData(parseableString);
		if( styleData->toString() == toStringResult ){
			return true;
		}else{
			cout << "\tcomparing " << styleData->toString() << " to " << toStringResult << endl;
			return false;
		}
	}
	
	template<class StyleDataType> 
	bool StyleTest_App::test_Clone(StyleDataType* styleData){
		StyleDataType* clonedData = dynamic_cast<StyleDataType*>(styleData->clone());
		
		if(styleData->getValue() == clonedData->getValue() ){
			return true;
		}else{
			return false;
		}
		delete clonedData;
	}	

	template<class StyleDataType> 
	void StyleTest_App::test_StyleData(const string& sdataName, const string& parseData, const string& toStringResult){
		cout << "testStyleData(\"" << sdataName <<"\")"<<endl;
		
		StyleDataType* sdata = new StyleDataType();
		if( !test_ParseData_ToString<StyleDataType>(sdata, parseData, toStringResult) ){
			cout << "\t FAILED: ParseData_ToString test" << endl;
		}else{
			cout << "\t PASSED: ParseData_ToString test" << endl;
		}
		
		if( !test_Clone<StyleDataType>(sdata) ){
			cout << "\t FAILED: Clone test failed" << endl;
		}else{
			cout << "\t PASSED: ParseData_ToString test" << endl;
		}
		delete sdata;
	}

	template<class StyleDataType, typename DataType>
	void StyleTest_App::testSingleStyle(const string& styleName, 
										DataType initValue,
										const string& parseData, 
										const string& toStringResult){
		cout << "testSingleStyle(\"" << styleName<<"\")"<<endl;
		StyleDataType* sdata = new StyleDataType();
		sdata->setValue(initValue);
		
		SingleStyle* ss = new SingleStyle(styleName, sdata);
		bool passedTests = true;
		
		// Check getName 
		if( ss->getName() != styleName ){
			cout << "\t FAILED: getName_Test" << endl;
			passedTests = false;
		}else{
			cout << "\t PASSED: getName_Test" << endl;
		}
		
		// Check getData
		StyleDataType* getSdata = dynamic_cast< StyleDataType* >(ss->getData());
		if( getSdata != NULL ){
			if (getSdata->getValue() != sdata->getValue() ){
				cout << "\t FAILED: getData_Test" << endl;
				passedTests = false;
			}
		}else {
			cout << "\t FAILED: getData_Test (getData returned incorrect StyleDataType pointer)" << endl;
			passedTests = false;
		}
		if( passedTests ){
			cout << "\t PASSED: getData_Test" << endl;
		}

		// Check parseData() and toString()
		ss->parseData(parseData);
		if( ss->toString() == toStringResult ){
			cout << "\t PASSED: parseData_toString_Test" << endl;
			passedTests = false;
		}else{
			
			cout << "\t FAILED: parseData_toString_Test.  " << ss->toString() << " != " << toStringResult << endl;
		}
		
		delete ss;
	}
		
	template<class StyleDataType, typename DataType>
	void StyleTest_App::testArrayStyle(	const string& styleName, 
										DataType initValues[],
										int size,
										const string& parseData, 
										const string& toStringResult	){
		cout << "Test ArrayStyle (\"" << styleName<< "\")" <<endl;
		
		ArrayStyle* ss = new ArrayStyle(styleName, new StyleDataType(), size);
		bool passedTests = true;
		
		// Check getName 
		if( ss->getName() != styleName ){
			cout << "\t FAILED: getName_Test (comparing " << ss->getName() << " != " << styleName << " )" << endl;
			passedTests = false;
		}else{
			cout << "\t PASSED: getName_Test" << endl;
		}
		
		// Check getData for setting and getting (by size)
		for(int i=0; i<size; ++i){
			StyleDataType* getSdata = dynamic_cast< StyleDataType* >(ss->getData(i));
			if( getSdata != NULL ){
				getSdata->setValue(initValues[i]);
			}else {
				cout << "\t FAILED: getData_Test (getData returned incorrect StyleDataType pointer)" << endl;
				passedTests = false;
			}
			
			StyleDataType* getSdata2 = dynamic_cast< StyleDataType* >(ss->getData(i));
			if( getSdata != NULL ){
				if( getSdata2->getValue() != initValues[i] ){
					DataType sdata2Value = getSdata2->getValue();
					cout << "\t FAILED: getData_Test, After Init Set ( ["<< i << "]=" << sdata2Value<< " != "<< initValues[i] << ")" << endl;  
					passedTests = false;
				}
			}else {
				cout << "\t FAILED: getData_Test, After Init Set (getData returned incorrect StyleDataType pointer)" << endl;
				passedTests = false;
			}
		}
		if( passedTests ){
			cout << "\t PASSED: getData_Test, After Init Set" << endl;
		}
		
		// Check parseData() and toString()
		ss->parseData(parseData);
		if( ss->toString() == toStringResult ){
			cout << "\t PASSED: ParseData_toString_Test" << endl;
			passedTests = false;
		}else{			
			cout << "\t FAILED: ParseData_toString_Test.  " << ss->toString() << " != " << toStringResult << endl;
		}
		
		delete ss;
	}
	
	void StyleTest_App::update_frame() throw(APPEXCEPTIONS) {
		
		cout << "************************" << endl;
		cout << "*** Style Data Tests ***" << endl;
		cout << "************************" << endl;
		test_StyleData<IntStyleData>("IntStyleData", "654", "654"); cout << endl;		
		test_StyleData<FloatStyleData>("FloatStyleData", "6.54", "6.54"); cout << endl;
		test_StyleData<ColorStyleData>("ColorStyleData", "#FFCC99", "#FFCC99");	cout << endl;
		cout << endl;
		
		cout << "**************************" << endl;
		cout << "*** Single Style Tests ***" << endl;
		cout << "**************************" << endl;
		testSingleStyle<IntStyleData, int>("TestIntStyleName",321,"654","TestIntStyleName: 654"); cout << endl;
		testSingleStyle<FloatStyleData, float>("TestFloatStyleName",1.23,"6.54","TestFloatStyleName: 6.54"); cout << endl;
		testSingleStyle<ColorStyleData, ColorHex>("TestColorStyleName",ColorHex(0.1, 0.2, 0.3, 0.4),"#FFCC99","TestColorStyleName: #FFCC99"); cout << endl;
		cout << endl;

		cout << "*************************" << endl;
		cout << "*** Array Style Tests ***" << endl;
		cout << "*************************" << endl;
		{	int 	initValues[] = {1};
			testArrayStyle<IntStyleData, int>("TestArrayIntStyleName",initValues,1,"[ 4 ]","TestArrayIntStyleName: [ 4 ]");
			cout << endl; }
		{	float 	initValues[] = {1.1,2.2,3.3,4.4};
			testArrayStyle<FloatStyleData, float>( "TestArrayFloatStyleName",
													initValues,
													4,
													"[ 4.4, 5.5, 6.6 ]",
													"TestArrayFloatStyleName: [ 4.4, 5.5, 6.6 ]");
			cout << endl; }
		{	ColorHex initValues[] = {ColorHex("#113355"), ColorHex("#224466")}; 
			testArrayStyle<ColorStyleData, ColorHex>(	"TestArrayColorStyleName",
														initValues,
														2,
														"[ #112233, #445566, #778899 ]",
														"TestArrayColorStyleName: [ #112233, #445566, #778899 ]");
			cout << endl; }
		cout << endl;
		
		cout << "***********************" << endl;
		cout << "*** Styleable Tests ***" << endl;
		cout << "***********************" << endl;
		
		
		getTenUI()->quit();				
	}
}

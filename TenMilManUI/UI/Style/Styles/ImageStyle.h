#ifndef IMAGESTYLE_H_
#define IMAGESTYLE_H_

#include <TenMilManUI/Graphics/IImage.h>
#include <TenMilManUI/TenUI_Globals.h>
#include <string>

using std::string;

namespace TenUI{
	class ImageStyle : public Style {
	public:
		ImageStyle(IImage* initValue){
			value = initValue;
		}
		ImageStyle(const string& initValue){
			value = getTenUIGraphics()->loadImage(initValue);
		}
		virtual ~ImageStyle(){ delete value; }
		
		virtual any getValue(){
			return value;
		}
		virtual void setValue(const any& newValue){
			
			if(value != 0){
				delete value;
			}
			
			const string* svalue = any_cast<string>(&newValue);
			if(svalue){
				value = getTenUIGraphics()->loadImage(*svalue);
				return;
			}
			

			IImage* const* cvalue = any_cast<IImage*>(&newValue);
			if(cvalue){
				value = *cvalue;
				return;
			}
		}
		virtual shared_ptr<Style> clone(){
			shared_ptr<ImageStyle> newInst(new ImageStyle(value));
			newInst->declaration = declaration;
			return newInst;
		}
		
	protected: 
		IImage* value;
	};
}

#endif /*IMAGESTYLE_H_*/

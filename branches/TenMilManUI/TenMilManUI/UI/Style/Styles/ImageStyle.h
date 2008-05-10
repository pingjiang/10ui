#ifndef IMAGESTYLE_H_
#define IMAGESTYLE_H_

#include <TenMilManUI/Graphics/IImage.h>
#include <TenMilManUI/Util/SmartPointer.h>
#include <TenMilManUI/TenUI_Globals.h>

#include <string>

using std::string;

namespace TenUI{
	class ImageStyle : public Style {
	public:
		ImageStyle(const sp<IImage>& initValue){
			hasInit = true;
			value = initValue;
		}
		ImageStyle(const string& initValue){
			urlString = initValue;
			hasInit = false;
		}
		virtual ~ImageStyle(){ }
		
		virtual any getValue(){
			if( !hasInit ){
				value = getTenUIGraphics()->loadImage(urlString);
				return value; 
			}
			return value;
		}
		virtual void setValue(const any& newValue){
			
			const string* svalue = any_cast<string>(&newValue);
			if(svalue){
				value = getTenUIGraphics()->loadImage(*svalue);
				return;
			}
			

			sp<IImage> const* cvalue = any_cast< sp<IImage> >(&newValue);
			if(cvalue){
				value = *cvalue;
				return;
			}
		}
		virtual sp<Style> clone(){
			sp<ImageStyle> newInst(new ImageStyle(value));
			newInst->declaration = declaration;
			return newInst;
		}
		
	protected: 
		bool hasInit;
		string urlString;
		sp<IImage> value;
	};
}

#endif /*IMAGESTYLE_H_*/

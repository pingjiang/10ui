#ifndef IMAGESTYLE_H_
#define IMAGESTYLE_H_

#include <TenMilManUI/Graphics/IImage.h>
#include <TenMilManUI/TenUI_Globals.h>
#include <string>
#include <tr1/memory>

using std::string;
using std::tr1::shared_ptr;

namespace TenUI{
	class ImageStyle : public Style {
	public:
		ImageStyle(const shared_ptr<IImage>& initValue){
			value = initValue;
		}
		ImageStyle(const string& initValue){
			value = getTenUIGraphics()->loadImage(initValue);
		}
		virtual ~ImageStyle(){ }
		
		virtual any getValue(){
			return value;
		}
		virtual void setValue(const any& newValue){
			
			const string* svalue = any_cast<string>(&newValue);
			if(svalue){
				value = getTenUIGraphics()->loadImage(*svalue);
				return;
			}
			

			shared_ptr<IImage> const* cvalue = any_cast< shared_ptr<IImage> >(&newValue);
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
		shared_ptr<IImage> value;
	};
}

#endif /*IMAGESTYLE_H_*/

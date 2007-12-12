#ifndef COLORHEX_H_
#define COLORHEX_H_

#include <string>
#include <ostream>
#include <iostream>

using std::string;
using namespace std;

namespace TenUI {
	
	class ColorHex {
	private:
		float colorv[4];
		
		int hexCharToInt(char c){
			if(c <= '9' && c >= '0'){
				return (int)c-'0';
			}else if(c <= 'F' && c >= 'A'){
				return (int)c-'A'+11;
			}else if(c <= 'f' && c >= 'a'){
				return (int)c-'a'+11;
			}
			return 0;
		}
		
		string intToChar(int val){
			if(val <= 9 && val >= 0){
				return string(1,val+'0');
			}else if(val <= 16 && val >= 10){
				return string(1,(val-10)+'A');
			}else{
				return string("0");
			}
		}

	public:
		static const ColorHex NoColor;
		
	public:
		ColorHex(const ColorHex &b){
			colorv[0] = b.colorv[0];
			colorv[1] = b.colorv[1];
			colorv[2] = b.colorv[2];
			colorv[3] = b.colorv[3];
		}
	
		ColorHex(float r, float g, float b, float a=1.0){
			colorv[0] = r;
			colorv[1] = g;
			colorv[2] = b;
			colorv[3] = a;
		}
			
		ColorHex(const string &ch){
			setColor(ch);
		}
		
		ColorHex(){
			colorv[0] = 0.0;
			colorv[1] = 0.0;
			colorv[2] = 0.0;
			colorv[3] = 0.0;
		}
				
		const ColorHex& operator =(const ColorHex& ch){
			colorv[0] = ch.colorv[0];
			colorv[1] = ch.colorv[1];
			colorv[2] = ch.colorv[2];
			colorv[3] = ch.colorv[3];
			return (*this);
		}
		
		bool operator ==(const ColorHex& ch2) const {
			if(	ch2.colorv[0] == colorv[0] &&
				ch2.colorv[1] == colorv[1] &&
				ch2.colorv[2] == colorv[2] &&
				ch2.colorv[3] == colorv[3]){
				return true;
			}
			return false;
		}
		

		bool operator!=(const ColorHex& ch2) const {
			return !((*this)==ch2);
		}
		
		string toString(){
			string result("#");
			for(unsigned int i=0; i < 3; ++i){
				int c = (int)(colorv[i]*255.0); 
				int hex1 = c>>4;
				int hex2 = c - (hex1<<4);
				
				result += intToChar(hex1);
				result += intToChar(hex2);								
			}
			return result;
		}
		
		void setColor(const string &ch){
			if(ch.at(0) == '#'){
				if(ch.size() == 7){
					for(int i=0; i<3; ++i){
						colorv[i] = ((float)(hexCharToInt(ch.at(i*2+1))*16+hexCharToInt(ch.at(i*2+2))))/255.0;
					}
				}else if(ch.size() == 4){
					for(int i=0; i<3; ++i){
						colorv[i] = ((float)(hexCharToInt(ch.at(i+1))))/16.0;
					}
				}
			}else{
				colorv[0] = 0;
				colorv[1] = 0;
				colorv[2] = 0;
			}
			colorv[3] = 1.0;
		}	
	
		float getRed() const {
			return colorv[0];
		}
		float getGreen() const {
			return colorv[1];
		}
		float getBlue() const {
			return colorv[2];
		}
		float getAlpha() const {
			return colorv[3];
		}
		
		void setRed(float r){
			colorv[0] = r;
		}
		void setGreen(float g){
			colorv[1] = g;
		}
		void setBlue(float b){
			colorv[2] = b;
		}
		void setAlpha(float a){
			colorv[3] = a;
		}
		const ColorHex& multModifyAlpha(float a){
			colorv[3] *= a;
			return (*this);
		}
		
		virtual ~ColorHex(){};

	};


	ostream& operator <<(ostream& os, ColorHex& ch);
}

#endif /*COLORHEX_H_*/

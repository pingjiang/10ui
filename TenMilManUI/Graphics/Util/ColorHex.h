#ifndef COLORHEX_H_
#define COLORHEX_H_

#include <string>
#include <iostream>

using std::string;
using namespace std;

class ColorHex {
private:
	float colorv[3];
	int hexCharToInt(char c){
		if(c <= '9' && c >= '0'){
			return (int)c-'0';
		}else if(c <= 'F' && c >= 'A'){
			return (int)c-'A'+10;
		}else if(c <= 'f' && c >= 'a'){
			return (int)c-'a'+10;
		}
		return 0;
	}
	
public:

	ColorHex(ColorHex &b){
		colorv[0] = b.colorv[0];
		colorv[1] = b.colorv[1];
		colorv[2] = b.colorv[2];
	}

	ColorHex(){
		colorv[0] = 0;
		colorv[1] = 0;
		colorv[2] = 0;
	}
	
	ColorHex(const string &ch){
		setColor(ch);
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
	}	

	float getRed(){
		return colorv[0];
	}
	float getGreen(){
		return colorv[1];
	}
	float getBlue(){
		return colorv[2];
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
	
	virtual ~ColorHex();
};

#endif /*COLORHEX_H_*/

#include "ArrayStyle.h"

#include <iostream>
using namespace std;

namespace TenUI{

	void ArrayStyle::stripWhiteSpace(string& in){
		int i = 0;
		for(; i<in.size(); ++i){
			if(	in[i] != ' ' 	&&
				in[i] != '\t' 	&& 
				in[i] != '\n'){
				break;
			}
		}
		if(i==in.size()){
			in.clear();
			return;
		}else{
			in.erase(0,i);
		}
		
		// take the stuff off the end
		for(i=in.size()-1; i>=0; --i){
			if(	in[i] != ' ' 	&&
				in[i] != '\t' 	&& 
				in[i] != '\n'){
				break;
			}
		}
		if(i==-1){
			in.clear();
			return;
		}else{
			in.erase(i+1,in.size()-i-1);
		}
	}

	bool ArrayStyle::tokenize(	const string& strc,
	              				vector<string>& tokens)
	{
		string delimiters(",");
		string str = strc;
		stripWhiteSpace(str);
		
	    // Skip delimiters at beginning.
	    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	    // Find first "non-delimiter".
	    string::size_type pos     = str.find_first_of(delimiters, lastPos);
	    
	    bool foundBeginning = false;
	    bool foundEnding = false;
	    
	    while ( !foundEnding && (string::npos != pos || string::npos != lastPos) )
	    {
	    	if( pos == string::npos ){
	    		pos = str.size();
	    	}
	    	if( str[lastPos] == '[' ){
	    		++lastPos;
	    		foundBeginning = true;
	    	}
	    	if( str[pos-1] == ']' ){
	    		--pos;
	    		foundEnding = true;
	    	}
	    	
	        // Found a token, add it to the vector.
	    	if( foundBeginning ){
	    		string tok = str.substr(lastPos, pos - lastPos);
	    		stripWhiteSpace( tok );
		        tokens.push_back( tok );
	    	}
	        
	        // Skip delimiters.  Note the "not_of"
	        lastPos = str.find_first_not_of(delimiters, pos);
	        // Find next "non-delimiter"
	        pos = str.find_first_of(delimiters, lastPos);
	    }
	    
	    return (foundBeginning && foundEnding);
	}
	
	void ArrayStyle::clearArray(){
		vector< StyleData* >::iterator it = array.begin();
		while(it != array.end()){
			delete (*it);
			++it;
		}
		array.clear();
	}
	
	ArrayStyle::ArrayStyle(const string& nm, StyleData *dt, int arraySize)
		:Style(nm),
		dataType(dt){
		while((arraySize--)>0){
			array.push_back(dt->clone());
		}
	}
	ArrayStyle::~ArrayStyle(){
		clearArray();
	}
	
	StyleData* ArrayStyle::getData(unsigned int i){
		if(i>=0 && i<array.size()){
			return array[i];
		}
		return NULL;
	}
			
	string ArrayStyle::toString(){
		string result(name+": [ ");
					
		vector< StyleData* >::iterator it = array.begin();
		if(it != array.end()){
			result += (*it)->toString();
		}
		while( (++it) != array.end() ){
			result += (", "+(*it)->toString());
		}
		
		result += " ]";
		return result;
	}
	void ArrayStyle::parseData(const string& str){
		clearArray();
		
		vector< string > toks;
		if( tokenize(str, toks) ){
			if(toks.size() > 0){
				vector< string >::iterator it = toks.begin();
				while(it != toks.end()){
					StyleData* sdata = dataType->clone();
					sdata->parseData((*it));
					array.push_back(sdata);
					++it;
				}
			}		
		}		
	}

	Style* ArrayStyle::clone(){
		ArrayStyle* cloned = new ArrayStyle(name, dataType->clone(), array.size());
		for(int i=0; i<array.size(); ++i){
			cloned->array[i] = array[i]->clone();
		}
		return cloned;
	}
	
}

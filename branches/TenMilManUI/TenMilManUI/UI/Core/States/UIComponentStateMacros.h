#ifndef UICOMPONENTSTATEMACROS_H_
#define UICOMPONENTSTATEMACROS_H_


#define DECL_STATE(theStateClass, theSuperClass, theStateName) 							\
	public:																				\
		static string getStateName(){ return #theStateName; }							\
		theStateClass(const string& name=#theStateName):theSuperClass(name){ cout << "\t" << #theStateClass << "(): " << name << endl; }	\
		virtual sp<UIComponentState> clone(){ return dynamic_pointer_cast<UIComponentState>(sp<theStateClass>(new theStateClass(getStateName()))); } 
		

#endif /*UICOMPONENTSTATEMACROS_H_*/

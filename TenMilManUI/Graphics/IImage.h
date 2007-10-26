#ifndef IIMAGE_H_
#define IIMAGE_H_

namespace TenUI{

	class IImage {
	public:
		virtual ~IImage(){};
		virtual unsigned int getImageWidth() = 0;
		virtual unsigned int getImageHeight() = 0;
	};

}

#endif /*IIMAGE_H_*/

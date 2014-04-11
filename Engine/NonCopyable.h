#pragma once
#ifndef id18014214_B5D7_4290_81CE5527266ECB70
#define id18014214_B5D7_4290_81CE5527266ECB70

namespace engine {

class NonCopyable {
protected:
	NonCopyable(){}
	~NonCopyable(){}
private:
	NonCopyable(const NonCopyable& other){}
	const NonCopyable& operator=(const NonCopyable& other){return *this;}
};

}

#endif 
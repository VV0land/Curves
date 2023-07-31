#include "pch.h"
#include "D3ll.h"

#include <iostream>

MY3DCURVESDLL::MY3DCURVESDLL() {

}

MY3DCURVESDLL::~MY3DCURVESDLL() {

}

void MY3DCURVESDLL::sayHello() {

	std::cout << "Hello from the Badprog DLL! :D" << std::endl;

}


// ============================================================================

//

// ============================================================================

void MY3DCURVESDLL::sayGoodbye() {

	std::cout << "Goodbye from the Badprog DLL! :D" << std::endl;

}
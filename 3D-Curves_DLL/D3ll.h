#ifndef MY3DCURVESDLL_H

#define MY3DCURVESDLL_H


#ifdef MY3DCURVESDLL_EXPORTS	//BADPROGDYNAMICLIBRARY_EXPORTS

#define API_MY3DCURVESDLL __declspec(dllexport)

#else

#define API_MY3DCURVESDLL __declspec(dllimport)

#endif


// Badprog.com


class API_MY3DCURVESDLL MY3DCURVESDLL {

	// ============================================================================

	//

	// ============================================================================

public:

	MY3DCURVESDLL();

	~MY3DCURVESDLL();


	// ============================================================================

	//

	// ============================================================================

public:

	void sayHello();

	void sayGoodbye();

};


#endif // !MY3DCURVESDLL_H
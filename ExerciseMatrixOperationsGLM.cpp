/****************************************************
 * 2016-2020 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted..
 ****************************************************/
/*
#include "Utilities.h"
 /*
	  | 1 |
 V1 = | 2 |
	  | 3 |

	  | -1 |
 V2 = | -2 |
	  | -3 |

		 | 1 2 3 |
 M3x3A = | 0 1 2 |
		 | 3 1 0 |

		 | 1 2 0 |
 M3x3B = | 2 4 0 |
		 | 3 0 1 |

		 | 10  0  0 |
 M3x3C = |  0 10  0 |
		 |  0  0 10 |
 */
//int main(int argc, char* argv[]) {
//	dvec3 V1(1, 2, 3);
//	dvec3 V2(-1, -2, -3);
//
//	dmat2 M2x2A(2, 4, 1, 2);
//
//	dmat3 M3x3A(1, 0, 3, 2, 1, 1, 3, 2, 0);
//	dmat3 M3x3B(1, 2, 3, 2, 4, 0, 0, 0, 1);
//	dmat3 M3x3C(10, 0, 0, 0, 10, 0, 0, 0, 10);
//
//	vector<dmat3> vecMats = { M3x3A, M3x3B, M3x3C };
//	vector<dvec3> vecVecs = { V1, V2 };
//
//	cout << "Get row: " << endl;
//	cout << getRow(M3x3A, 0) << endl;			// [1 2 3]
//	cout << getRow(M3x3A, 1) << endl;			// [0 1 2]
//	cout << getRow(M3x3A, 2) << endl << endl;	// [3 1 0]
//
//	cout << "Get col: " << endl;
//	cout << getCol(M3x3A, 0) << endl;			// [1 0 3]
//	cout << getCol(M3x3A, 1) << endl;			// [2 1 1]
//	cout << getCol(M3x3A, 2) << endl << endl;	// [3 2 0]
//
//	cout << "Is invertible: " << endl;
//	cout << isInvertible(M3x3A) << endl;		// 1
//	cout << isInvertible(M3x3B) << endl;		// 0
//	cout << isInvertible(M3x3C) << endl << endl;// 1
//
//	cout << "Solve linear system: " << endl;
//	cout << solveLinearSystem(M3x3A, V1) << endl;			// [ 7 -18 10 ]
//	cout << solveLinearSystem(M3x3B, V1) << endl;			// [ 0 0 0 ]
//	cout << solveLinearSystem(M3x3C, V1) << endl << endl;	// [ 0.1 0.2 0.3 ]
//
//	cout << "Add matrices: " << endl;
//	cout << addMatrices(vecMats) << endl << endl;
//	/*
//	|             12               4               3        |
//	|              2              15               2        |
//	|              6               1              11        |
//	*/
//
//	cout << "multiplyMatrices: " << endl;
//	cout << multiplyMatrices(vecMats) << endl << endl;
//	/*
//	|            140             100              30        |
//	|             80              40              20        |
//	|             50             100               0        |
//	*/
//
//	cout << "multiplyMatrixAndVertex: " << endl;
//	cout << multiplyMatrixAndVertex(M3x3A, V1) << endl << endl;		// [ 14 8 5 ]
//
//	cout << "multiplyMatricesAndVertex: " << endl;
//	cout << multiplyMatricesAndVertex(vecMats, V1) << endl << endl;	// [ 430 220 250 ]
//
//	cout << "multiplyMatrixAndVertices: " << endl;
//	cout << multiplyMatrixAndVertices(M3x3A, vecVecs) << endl << endl;
//	/*
//	[
//			[ 14 8 5 ]
//			[ -14 -8 -5 ]
//	]
//	*/
//
//	cout << "multiplyMatricesAndVertices: " << endl;
//	cout << multiplyMatricesAndVertices(vecMats, vecVecs) << endl;
//	/*
//	[
//			[ 430 220 250 ]
//			[ -430 -220 -250 ]
//	]
//	*/
//
//	return 0;
//}
//*/
/* OUTPUT
Get row:
[ 1 2 3 ]
[ 0 1 2 ]
[ 3 1 0 ]

Get col:
[ 1 0 3 ]
[ 2 1 1 ]
[ 3 2 0 ]

Is invertible:
1
0
1

Solve linear system:
[ 7 -18 10 ]
[ 0 0 0 ]
[ 0.1 0.2 0.3 ]

Add matrices:

|             12               4               3        |
|              2              15               2        |
|              6               1              11        |

multiplyMatrices:

|            140             100              30        |
|             80              40              20        |
|             50             100               0        |

multiplyMatrixAndVertex:
[ 14 8 5 ]

multiplyMatricesAndVertex:
[ 430 220 250 ]

multiplyMatrixAndVertices:
[
		[ 14 8 5 ]
		[ -14 -8 -5 ]
]

multiplyMatricesAndVertices:
[
		[ 430 220 250 ]
		[ -430 -220 -250 ]
]
*/



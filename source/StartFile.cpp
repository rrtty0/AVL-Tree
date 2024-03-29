#include "Tree.h"

int main()
{
	Tree A;
	A.add(1);                    //added only for demonstration function add(int)
	cout << "Tree 'A':";
	A.printTree();
	cout << "\n\n";
	
	Tree B({0,1,2,3,4,5,6});
	B.remove(3);                 //added only for demonstration function remove(int)
	cout << "Tree 'B':";
	B.printTree();
	cout << "\n\n";

	Tree C({ 9,7 });
	cout << "Tree 'C':";
	C.printTree();
	cout << "\n\n";

	Tree D({ 5,4,3 });
	cout << "Tree 'D':";
	D.printTree();
	cout << "\n\n";

	Tree E({ 1,2 });
	cout << "Tree 'E':";
	E.printTree();
	cout << "\n\n";
	
	Tree result;
	cout << "Tree 'result':";
	result = A & B | C | (D + E);
	result.printTree();
	cout << "\n\n";

	system("pause");
    return 0;
}


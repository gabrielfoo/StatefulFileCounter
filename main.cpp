#include "StatefulFileCounter.h"
#include <iostream>


void localtest()
{
	StatefulFileCounter counter("Counter");
	counter--;
	std::cout << "localtest: " << counter.uiGetCount() << std::endl;
}

int main()
{
#if 0
	puts("Test case 1 : File shouldn't exist");
	StatefulFileCounter newfile("RandomNonExistentFile", 9);
	puts("");

	puts("Test case 2 : File exists (precreated file)");
	StatefulFileCounter existingfile("Counter", 33);
	puts("");

	puts("Test case 3 : Get count of previously newly created file (result should be 9)");
	std::cout << "Count: " << newfile.uiGetCount() << std::endl;
	puts("");

	puts("Test case 4 : Get count of pre-created file (result should be 33 (ascii of '!') despite having the optional 2nd param)");
	std::cout << "Count: " << existingfile.uiGetCount() << std::endl;
	puts("");

	puts("Test case 5 : New file created now should default to 0 if only first param is used");
	StatefulFileCounter zeroFile("zerofile");
	std::cout << "Count: " << zeroFile.uiGetCount() << std::endl;
	puts("");

	puts("Test case 6 : -- Operator overload test. Expected result: 32");
	std::cout << "--File: " << --existingfile << std::endl;
	puts("");

	puts("Test case 7 :  Operator overload -- (postfix) test. Expected result: 32, then 31");
	std::cout << "File--: " << existingfile-- << std::endl;
	std::cout << "Postfix deduction result: " << existingfile.uiGetCount() << std::endl;
	puts("");

	puts("Test case 8 : ++ Operator overload test. Expected result: 32");
	std::cout << "++File: " << ++existingfile << std::endl;
	puts("");

	puts("Test case 9 :  Operator overload ++ (postfix) test. Expected result: 32, then 33");
	std::cout << "File++: " << existingfile++ << std::endl;
	std::cout << "Postfix addition result: " << existingfile.uiGetCount() << std::endl;
	puts("");

	puts("Test case 10 :  assignment operator overload test. Expected result: 44");
	unsigned int a = existingfile;
	a += 11; //33+11
	existingfile = a;
	std::cout << "Result: " << existingfile.uiGetCount() << '\n';
	puts("");


	puts("Test case 11 :  Equality operator overload.");
	std::cout << "existingfile == 44 : (expected result true)" << ((existingfile == 44) ? "TRUE" : "FALSE") << '\n';
	std::cout << "existingfile == 33 : (false) " << ((existingfile == 33) ? "TRUE" : "FALSE") << '\n';
	std::cout << "Existingfile value: " << existingfile.uiGetCount() << '\n';
	puts("");

	puts("Test case 12 : for loop test");
	for (; existingfile > 20; existingfile--)
	{
		std::cout << "Existingfile value: " << existingfile.uiGetCount() << '\n';
	}
	puts("");

	puts("Test case 13 : for loop test (addition)");
	for (; existingfile <= 50; existingfile++)
	{
		std::cout << "Existingfile value (addition): " << existingfile.uiGetCount() << '\n';
	}
	puts("");

	puts("Test case 14 : for loop test (in func declared locally)");
	for (int i = 0; i < 10; i++)
	{
		localtest();
	}
	puts("");
#endif

	puts("Exit time");
	StatefulFileCounter rebootCount("rebootCount", 3);
	if (rebootCount != 0)
	{
		rebootCount--;
		puts("Exiting...");
		exit(0);
	}
	else
	{
		std::cout << "rebootCount value: " << rebootCount.uiGetCount() << std::endl;
		rebootCount = 2;
		std::cout << "rebootCount value: " << rebootCount.uiGetCount() << std::endl;
	}

}
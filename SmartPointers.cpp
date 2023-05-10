#include <iostream>
#include<memory>
#include "MySmartPointers.h"
//Создайте пользовательские классы умных указателей.
//Один из классов должен повторять функциональность стандартного класса unique_ptr, а другой shared_ptr.
//Напишите код по тестированию ваших классов.


int main()
{
	std::cout << "Testing Unique_ptr class_______________________________________________________________________________________" << std::endl;
	int* test = nullptr;
	MySmartPointers::Unique_ptr<int> myUniquePtr1(new int(11));
	MySmartPointers::Unique_ptr<int> myUniquePtr2(new int(22));
	//MySmartPointers::Unique_ptr<int> myUniquePtr2(myUniquePtr1); // использование конструктора копирования запрещено
	//myUniquePtr1 = myUniquePtr2; // копирование запрещено

	std::cout << "Unique_ptr1 addres: " << myUniquePtr1.Get() << "\tUnique_ptr1 Value: " << *myUniquePtr1 << std::endl;
	std::cout << "Unique_ptr2 addres: " << myUniquePtr2.Get() << "\tUnique_ptr2 Value: " << *myUniquePtr2 << std::endl;
	myUniquePtr1.Reset(new int(33));
	std::cout << "Unique_ptr1 addres after Reset: " << myUniquePtr1.Get() << "\tUnique_ptr1 Value: " << *myUniquePtr1 << std::endl;
	myUniquePtr2.Swap(myUniquePtr1);
	std::cout << "Unique_ptr1 addres after Swap: " << myUniquePtr1.Get() << "\tUnique_ptr1 Value: " << *myUniquePtr1 << std::endl;
	std::cout << "Unique_ptr2 addres after Swap: " << myUniquePtr2.Get() << "\tUnique_ptr2 Value: " << *myUniquePtr2 << std::endl;
	test = myUniquePtr1.Release();
	std::cout << "Test addres after RELEASE Unique_ptr1: " << test <<  "\tTest value after RELEASE Unique_ptr1: " << *test << std::endl;
	std::cout << "_______________________________________________________________________________________________________________" << std::endl;


	std::cout << std::endl << "Testing Shared_ptr class_______________________________________________________________________________________" << std::endl;
	MySmartPointers::Shared_ptr<int> mySharedPtr1(new int(77));
	MySmartPointers::Shared_ptr<int> mySharedPtr2;
	MySmartPointers::Shared_ptr<int> mySharedPtr3(mySharedPtr1);
	MySmartPointers::Shared_ptr<int> mySharedPtr4(new int(444));
	std::cout << "mySharedPtr1 addres: " << mySharedPtr1.Get() << "\tmySharedPtr1 Value: " << *mySharedPtr1 << std::endl;
	std::cout << "mySharedPtr3 addres: " << mySharedPtr3.Get() << "\tmySharedPtr3 Value: " << *mySharedPtr3 << std::endl;
	std::cout << "mySharedPtr4 addres: " << mySharedPtr4.Get() << "\tmySharedPtr4 Value: " << *mySharedPtr4 << std::endl;

	mySharedPtr2 = mySharedPtr1;
	std::cout << std::endl << "mySharedPtr2 addres: " << mySharedPtr2.Get() << "\tmySharedPtr2 Value: " << *mySharedPtr2 << std::endl;
	std::cout << std::endl << "mySharedPtr1 object count: " << mySharedPtr1.Use_count();
	std::cout << std::endl << "mySharedPtr2 object count: " << mySharedPtr2.Use_count();
	std::cout << std::endl << "mySharedPtr3 object count: " << mySharedPtr3.Use_count();
	std::cout << std::endl << "mySharedPtr4 object count: " << mySharedPtr4.Use_count() << std::endl;
	mySharedPtr4.Swap(mySharedPtr2);
	std::cout << std::endl << "mySharedPtr2 addres after Swap: " << mySharedPtr2.Get() << "\tmySharedPtr2 Value: " << *mySharedPtr2 << std::endl;
	std::cout << "mySharedPtr4 addres after Swap: " << mySharedPtr4.Get() << "\tmySharedPtr4 Value: " << *mySharedPtr4;
	std::cout << std::endl << "mySharedPtr1 object count: " << mySharedPtr1.Use_count();
	std::cout << std::endl << "mySharedPtr2 object count: " << mySharedPtr2.Use_count();
	std::cout << std::endl << "mySharedPtr3 object count: " << mySharedPtr3.Use_count();
	std::cout << std::endl << "mySharedPtr4 object count: " << mySharedPtr4.Use_count() << std::endl;

	mySharedPtr3.Reset(new int(333));
	std::cout << std::endl << "mySharedPtr3 addres after Reset: " << mySharedPtr3.Get() << "\tmySharedPtr3 Value: " << *mySharedPtr3;
	std::cout << std::endl << "mySharedPtr1 object count: " << mySharedPtr1.Use_count();
	std::cout << std::endl << "mySharedPtr2 object count: " << mySharedPtr2.Use_count();
	std::cout << std::endl << "mySharedPtr3 object count: " << mySharedPtr3.Use_count();
	std::cout << std::endl << "mySharedPtr4 object count: " << mySharedPtr4.Use_count() << std::endl;
}
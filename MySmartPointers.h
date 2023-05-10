#include <iostream>
namespace MySmartPointers
{
	using namespace std;
	// -------------------------------------------------------------------------------------------------------------------
	//----- класс Unique_ptr повторяет частично, без поддержки динамических массивов, функциональность стандартного класса
	template <typename T>
	class Unique_ptr
	{
		T* ptr;
	public:
		explicit Unique_ptr(T* ptr = nullptr) : ptr{ ptr } {}
		Unique_ptr(const Unique_ptr& obj) = delete; // запрет конструктора копирования
		Unique_ptr(Unique_ptr&& obj) : ptr{ obj.ptr }// конструктор перемещения
		{
			obj.ptr = nullptr;
		}
		Unique_ptr& operator=(const Unique_ptr& obj) = delete;// запрет оператора копирования
		Unique_ptr& operator=(Unique_ptr&& obj) // оператор перемещения
		{
			if (this != &obj)
			{
				delete this->ptr;
				this->ptr = obj.ptr;
				obj.ptr = nullptr;
			}
			return *this;
		}

		T* operator->()const { return this->ptr; }
		T& operator*() const { return *this->ptr; }
		explicit operator bool() const { return this->ptr != nullptr; }
		T* Get() const { return this->ptr; }
		void Reset(T* newptr = nullptr)
		{
			if (this->ptr != newptr)
			{
				delete this->ptr;
				this->ptr = newptr;
			}
		}
		T* Release()
		{
			T* temp = this->ptr;
			this->ptr = nullptr;
			return temp;
		}

		void Swap(Unique_ptr& obj)
		{
			std::swap(this->ptr, obj.ptr);
		}

		~Unique_ptr()
		{
			if (this->ptr)
			{
				delete this->ptr;
				this->ptr = nullptr;
			}
		}
	};


	// -------------------------------------------------------------------------------------------------------------------
	//----- класс Shared_ptr повторяет частично, без поддержки динамических массивов, функциональность стандартного класса
	// контроль кол-ва объектов осуществляется только через получение адреса объекта посредством конструктора копирования или оператора копирования
	template <typename T>
	class Shared_ptr
	{
		T* ptr;
		int* count;		// в этой ячейке хранится кол-во объектов-указателей, указывающих на контролируемый объект
	public:
		explicit Shared_ptr(T* ptr = nullptr) : ptr{ ptr }
		{
			this->count = new int(1);
		}

		// Конструктор копирования
		Shared_ptr(const Shared_ptr& obj) : ptr(obj.ptr), count(obj.count)
		{
			if (this->count)
			{
				++(*this->count);
			}
		}

		// Оператор присваивания
		Shared_ptr& operator=(const Shared_ptr& obj)
		{
			if (this != &obj)
			{
				if (this->count)
				{
					(*this->count)--;
					if (*count == 0)
					{
						delete ptr;
						delete count;
					}
				}
				this->ptr = obj.ptr;
				this->count = obj.count;
				if (this->count)
				{
					(*this->count)++;
				}
			}
			return *this;
		}


		T& operator*() const 		// Оператор индексации
		{
			return *ptr;
		}


		T* operator->() const		// Оператор разименовывания
		{
			return this->ptr;
		}


		T* Get() const 				// Возвращает указатель на управляемый объект
		{
			return this->ptr;
		}


		int Use_count() const 		// Возвращает количество shared_ptr объектов, ссылающихся на управляемый объект
		{
			return (this->count ? *this->count : 0);
		}


		void Swap(Shared_ptr& obj)
		{
			std::swap(this->ptr, obj.ptr);
			std::swap(this->count, obj.count);
		}

		void Reset(T* newptr = nullptr)
		{
			if (newptr != this->ptr)
			{
				if (this->count && --(*this->count) == 0)
				{
					delete this->ptr;
					delete this->count;
				}
				this->ptr = newptr;
				this->count = new int(1);
			}
		}


		~Shared_ptr()
		{
			if (this->count)
			{
				--(*this->count);
				if (*this->count == 0)
				{
					delete this->ptr;
					delete this->count;
				}
			}
			this->ptr = nullptr;
			this->count = nullptr;

		}
	};

}

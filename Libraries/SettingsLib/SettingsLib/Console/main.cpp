#include <iostream>
#include <vector>

class A
{
	public:
		union uA
		{
			std::vector<int>* pv;
			int* pi;
			double d;
		};

		uA d;
		std::string name;
		int t = 0;

		A(std::vector<int> v, std::string name)
		{
			t = 1;
			this->name = name;
			this->d.pv = new std::vector<int>;
			*this->d.pv = v;
		}

		A(int i, std::string name)
		{
			t = 2;
			this->name = name;
			this->d.pi = new int;
			*this->d.pi = i;
		}

		A(double d, std::string name)
		{
			t = 3;
			this->name = name;
			this->d.d = d;
		}

		~A()
		{
			std::cout << "Destructor called for object " << this->name << " with data type (" << this->t << "). Using " << sizeof(uA) << " bytes for uA union type. ";
			
			switch (this->t)
			{
				case 1:
				{
					std::cout << "Using " << sizeof(this->d.pv) << " bytes for vector";
					delete this->d.pv;
					this->d.pv = nullptr;
					break;
				}
				case 2:
				{
					std::cout << "Using " << sizeof(this->d.pi) << " bytes for int*";
					delete this->d.pi;
					this->d.pi = nullptr;
					break;
				}
				case 3:
				{
					std::cout << "Using " << sizeof(this->d.d) << " bytes for double";
				}
				default:
				{
					break;
				}
			}

			std::cout << std::endl;
		}
};

int main (int argc, const char* argv[], const char* argp[])
{
	std::cout << "Test Console" << std::endl;

	A obj1(std::vector<int>{1,2,3,4,5}, "obj 1");
	A obj2(12, "obj 2");
	A obj3(3.14, "obj 3");

	std::vector<int>* v1 = obj1.d.pv;

	std::cout << "Vector: ";
	for (size_t i = 0; i < v1->size(); i++)
	{
		std::cout << " " << v1->at(i);
	}
	std::cout << std::endl;

	std::cout << "Int pointer: " << *obj2.d.pi << std::endl;

	std::cout << "Double: " << obj3.d.d << std::endl;

	obj1.~A();
	obj2.~A();
	obj3.~A();

	return 0;
}
#include<functional>
#include <iostream>

int call(int param)
{
	std::cout << "rpc"<<param<<"\n";
	return 0;
}

int main()
{
	auto _call=	std::bind<int(int),int >(call, 10);
	_call();

}
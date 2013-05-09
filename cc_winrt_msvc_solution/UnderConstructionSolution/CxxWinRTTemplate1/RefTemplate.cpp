// RefTemplate.cpp : Defines the entry point for the console application.
//

#include <iostream>
using namespace std;

using namespace Platform;


int main(Platform::Array<Platform::String^>^ args)
{
    Platform::Guid g;
    auto s = g.ToString();
    auto sd = s->Data();
	return 0;
}


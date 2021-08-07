// PIMPL_Tst.ixx
//export module PIMPL_Tst;

//export void MyFunc();

// https://docs.microsoft.com/en-us/cpp/cpp/import-export-module?view=msvc-160
// Place a module declaration at the beginning of a module implementation file to specify that the file contents belong to the named module.
module;
#include <memory>
#include <iostream>
export module PIMPL_Tst;
struct Impl;

export
class S {
public:
	S();
	~S();
	void do_stuff();
	Impl* get() const { return impl.get(); }
private:
	std::unique_ptr<Impl> impl;
};



module :private; // Everything beyond this point is not available to importers of 'm'.

struct Impl {
	void do_stuff() 
	{ 
		std::cout << "Impl::do_stuff\n";
	}
};

S::S() :
	impl{ std::make_unique<Impl>() }
{
	std::cout << "S::S\n";
}

S::~S() { }

void S::do_stuff() {
	std::cout << "S::do_stuff\n";
	impl->do_stuff();
}






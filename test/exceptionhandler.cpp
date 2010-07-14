#include <cstdlib>
#include <exception>
#include <iostream>

namespace
{
	void globalexcept()
	{
		try
		{
			throw;
		}
		catch(std::exception& ex)
		{
			std::cerr << "Unhandled exception :: " << ex.what() << std::endl;
		}
		catch(...)
		{
			std::cerr << "Unknown exception occurred\n";
			std::abort();
		}

		std::exit(1);
	}

	class _registerExceptionHandler
	{
		public:
		_registerExceptionHandler()
		{
			std::set_terminate(globalexcept);
		}
	};

	_registerExceptionHandler regExcptHandler;
}

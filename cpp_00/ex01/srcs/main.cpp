#include "../header/PhoneBook.hpp"
#include <iostream>

int	main(void)
{
	PhoneBook book;

	while (!book.exit)
	{
		if (std::cin.eof())
			return (0);
		book.prompt();
	}
}
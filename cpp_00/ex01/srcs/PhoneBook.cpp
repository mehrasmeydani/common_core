#include "../header/PhoneBook.hpp"
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

PhoneBook::PhoneBook(void)
{
	len = 0;
	exit = 0;
	return ;
}
PhoneBook::~PhoneBook()
{
	return ;
}

void	PhoneBook::set_book(void)
{
	Contact 	newContact;
	std::string	input;

	if (len < 8)
	{
		newContact.set_conact();
		this->Contacts[this->len] = newContact;
		len++;
	}
	else
		this->Contacts[7].set_conact();
	return ;
}

void	PhoneBook::get_book()
{
	int	x = 0;
	std::string tmp;

	if (this->len == 0)
	{
		std::cout << "THE PHONEBOOK IS EMPTY!" << std::endl;
		return ;
	}
	while (x == 0)
	{
		std::cout << "PLEASE ENTER A NUMBER BETWEEN " << 1 << " AND " << len << std::endl;
		std::cin >> x;
		if (std::cin.eof())
		{
			this->exit = 1;
			return ;
		}
		if (std::cin.fail()) {
    		std::cin.clear();
    		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   			std::cout << "A NUMBER!" << std::endl;
			x = 0;
		}
		else if (x < 1 || x > len)
		{
			std::cout << "WOW YOU CAN'T FOLLOW INSTRUCTIONS" << std::endl;
			x = 0;
		}
		else
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	std::cout << std::left << std::setw(10) << x << std::flush;
	this->Contacts[x - 1].get_conact();
	return ;
}

void	PhoneBook::prompt()
{
	std::string input;
	std::cout << "PLEASE ENTER ONE OF THE FOLLOWING OPERATIONS!" << std::endl << "1.\t[ADD]: save a new contact\n2.\t[SEARCH]: display a specific contact\n3.\t[EXIT]: exit code\nEntered option:" << std::flush;
	std::getline(std::cin, input);
	if (input == "ADD")
		set_book();
	else if (input.compare("SEARCH") == 0)
		get_book();
	else if (input.compare("EXIT") == 0)
		this->exit = 1;
	return ;
}

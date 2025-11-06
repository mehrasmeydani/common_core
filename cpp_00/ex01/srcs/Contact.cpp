#include "../header/Contact.hpp"
#include <iostream>
#include <iomanip>

Contact::Contact(void)
{
	return ;
}

Contact::~Contact(void)
{
	return ;
}

void	Contact::get_conact(void)
{
	std::cout << "|" << std::left << std::setw(10) << this->first_name << "|" << std::left << std::setw(10) << this->last_name << "|" << std::left << std::setw(10) << this->last_name << std::endl;
}

void	Contact::set_conact(void)
{
	std::cout << "ENTER FIRST NAME: " << std::flush;
	std::getline(std::cin, this->first_name);
	std::cout << "ENTER LAST NAME: " << std::flush;
	std::getline(std::cin, this->last_name);
	std::cout << "ENTER NICKNAME: " << std::flush;
	std::getline(std::cin, this->nickname);
	std::cout << "ENTER PHONE NUMBER: " << std::flush;
	std::getline(std::cin, this->phone_number);
	std::cout << "ENTER DARKEST SECRET: " << std::flush;
	std::getline(std::cin, this->darkest_secret);
	return ;
}

#pragma once

# include "Contact.hpp"

class PhoneBook
{
	private:
		Contact	Contacts[8];
		int		len;
	public:
		PhoneBook(void);
		~PhoneBook(void);
		int		exit;

		void	set_book(void);
		void	get_book(void);
		void	prompt(void);

};

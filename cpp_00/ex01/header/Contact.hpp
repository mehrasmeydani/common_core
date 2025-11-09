#pragma once

# include <string>

class Contact
{
	public:
		Contact();
		~Contact();

	private:
		std::string first_name;
		std::string	last_name;
		std::string	nickname;
		std::string	phone_number;
		std::string	darkest_secret;
	
	public:
		void	set_conact(void);
		void	get_conact(void);
};

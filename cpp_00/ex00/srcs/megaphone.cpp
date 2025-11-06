#include <iostream>

int	main(int argc, char **argv)
{
	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			for (size_t j = 0; argv[i][j]; j++)
			{
				argv[i][j] = (char)toupper(argv[i][j]);
			}
			std::cout << argv[i] << std::flush;
		}
		std::cout << std::endl;
	}
	else
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
}
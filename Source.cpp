#include <iostream> 
#include <string> 

#include "Clock\Clock.h"
#include "Converter\Converter.h"

void PrintUsageMessage(void)
{
	std::cout << "\nOptions:\n";
	std::cout << "  -i [ --infile ] arg\tName of file to convert\n";
	std::cout << "  -o [ --outfile ] arg\tName of file generated after conversion\n";
	std::cout <<
		(std::string)"  --precision arg\t"
		+ "Real number that defines line deflection of model\n"
		+ "\t\t\tduring conversion (smaller number will result in better\n"
		+ "\t\t\tresolution of final model)\n";
	std::cout << "  -m\t\t\tCombine shape with its YOZ mirror\n";
	std::cout << "  -h [ --help ]\t\tPrint help(usage) messages\n";
}

int main(int argc, char* argv[])
{
	if (argc < 5)
	{
		std::cout << "\nERROR: Arguments missing\n";

		atexit(PrintUsageMessage);
		return EXIT_FAILURE;
	}

	std::string infile = std::string();
	std::string outfile = std::string();

	Clock clock;
	//Converter converter;

	for (int i = 1; i < argc; i++)
	{
		std::string currentArgument = argv[i];

		if (currentArgument == " ") continue;

		if (currentArgument == "-i" || currentArgument == "--infile")
		{
			i = i + 1;
			infile = argv[i];
		}
		else if (currentArgument == "-o" || currentArgument == "--outfile")
		{
			i = i + 1;
			outfile = argv[i];
		}
		else if (currentArgument == "--precision")
		{
			i = i + 1;
			double precision;

			try
			{
				precision = atof(argv[i]);
			}
			catch(int e)
			{
				std::cout << "\nERROR: precision argument not a number";
				std::cout << "(error: " << e << ")\n";
				atexit(PrintUsageMessage);

				return EXIT_FAILURE;
			}

			//converter.SetPrecision(precision);
		}
		else if (currentArgument == "-m")
		{
			//converter.SetMirror();
		}
		else if (currentArgument == "-h" || currentArgument == "--help")
		{
			PrintUsageMessage();

			if (i != 2)
			{
				std::cout << "Note: Due to involment of help command, only that action will be completed!\n";
			}

			return EXIT_SUCCESS;
		}
		else
		{
			std::cout << "\nERROR: Invalid arguments\n";

			atexit(PrintUsageMessage);
			return EXIT_FAILURE;
		}
	}

	if (infile == std::string())
	{
		std::cout << "\nERROR: the option '--infile' is required but missing\n";
		atexit(PrintUsageMessage);

		return EXIT_FAILURE;
	}

	if (outfile == std::string())
	{
		std::cout << "\nERROR: the option '--outfile' is required but missing\n";
		atexit(PrintUsageMessage);

		return EXIT_FAILURE;
	}

	std::cout << "Conversion started:\n";

	//converter.ReadFromFile(infile.c_str());
	//converter.WriteToFile(outfile.c_str());

	std::cout << "Conversion lasted: " << clock.ElapsedSeconds() << std::endl;

	return EXIT_SUCCESS;
}
#include "Compressor.h" 
#include "Decompressor.h"
#include <iostream> 
int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		FILE* fpin;
		FILE* fpout;
		FILE* fptable;
		if (!strcmp("-d", argv[1]))
		{
			std::cout << "------Decompressor------\n";
			if (argc == 4)
			{
				fpin = fopen(argv[2], "r");
				fpout = fopen(argv[3], "w");
				if (fpin == NULL)
				{
					std::cout << "File: " << argv[2] << " can not open.";
					return 0;
				}
				else
				{
					Decompressor d(fpin, fpout);
					char TableName[100];
					std::cout << "Input table name: ";
					std::cin >> TableName;
					FILE* fptable = fopen(TableName, "rt");
					d.Decompress(fptable);

				}
			}
		}
		if (!strcmp("-c", argv[1]))
		{
			std::cout << "------Compressor------\n";
			if (argc == 4)
			{
				fpin = fopen(argv[2], "r");
				fpout = fopen(argv[3], "w");

				if (fpin == NULL)
				{
					std::cout << "File: " << argv[2] << " can not open.";
					return 0;
				}
				else
				{
					Compressor c(fpin, fpout);
					char TableName[100];
					std::cout << "Input table name: ";
					std::cin >> TableName;
					FILE* fptable = fopen(TableName, "wt");
					c.Compress(fptable);
				}
			}
		}
	}
	else
	{
		char* InFileName = new char[100];
		char* OutFileName = new char[100];

		FILE* fpin;
		FILE* fpout;
		FILE* fptable;
		int mode = 0;

		while (true)
		{
			std::cout << "----------------------\n";
			std::cout << "1 --- Compressor\n";
			std::cout << "2 --- Decompressor\n";
			std::cout << "3 --- Exit\n";
			std::cout << "----------------------\n";
			std::cin >> mode;

			if (mode == 1)
			{
				std::cout << "------Compressor------\n";
				std::cout << "Input in file name: ";
				std::cin >> InFileName;


				std::cout << "Input out file name: ";
				std::cin >> OutFileName;
				fpin = fopen(InFileName, "rb");
				fpout = fopen(OutFileName, "wb");

				if (fpin == NULL)
				{
					std::cout << "File: " << InFileName << "can not open.";
					return 0;
				}
				else
				{
					Compressor a(fpin, fpout);

					char TableName[100];
					std::cout << "Input table name: ";
					std::cin >> TableName;
					fptable = fopen(TableName, "wt");
					a.Compress(fptable);
				}
			}
			else if (mode == 2)
			{
				std::cout << "-----Decompressor-----\n";

				std::cout << "Input in file name: ";
				std::cin >> InFileName;

				std::cout << "Input out file name: ";
				std::cin >> OutFileName;
				fpin = fopen(InFileName, "rb");

				if (fpin == NULL)
				{
					std::cout << "File: " << InFileName << " can not open.";
					return 0;
				}
				else
				{
					fpout = fopen(OutFileName, "wb");

					Decompressor b(fpin, fpout);

					char TableName[100];
					std::cout << "Input table name: ";
					std::cin >> TableName;
					fptable = fopen(TableName, "rt");

					if (fptable != NULL)
						b.Decompress(fptable);
				}

			}
			else
			{
				break;
			}

			fclose(fpin);
			fclose(fpout);
			fclose(fptable);
		}

	}
	return 0;
}
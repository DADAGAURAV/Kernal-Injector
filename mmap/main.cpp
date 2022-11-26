#include "mmap.hpp"
#include <vector>
HANDLE driver_handle;
bool find_driver() {
	driver_handle = CreateFileW((L"\\\\.\\\injdrv"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

	if (!driver_handle || (driver_handle == INVALID_HANDLE_VALUE))
		return false;

	return true;
}




void print(std::string text, int colorchoice)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// you can loop k higher to see more color choices
	// pick the colorattribute k you want
	SetConsoleTextAttribute(hConsole, colorchoice);
	// cout << text;
	for (int j = 0; j < text.size(); j++)
	{
		Sleep(15);
		std::cout << text[j];
	}
}
int main(int argc, char** argv)
{


	if (argc != 3) {
		std::cout << "[!] Incorrect usage. ( mmap.exe {process.exe} {path.dll} )" << std::endl;
		return 0;
	}

	mmap mapper(INJECTION_TYPE::KERNEL);
	mapper.attach_to_process(argv[1]);
	if (!mapper.attach_to_process(argv[1]))
		return 1;
	mapper.load_dll(argv[2]);
	if (!mapper.load_dll(argv[2]))
		return 1;
	mapper.inject();
	if (!mapper.inject())
		return 1;

	return 0;
}
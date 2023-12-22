#include <iostream>
#include "swnLibrary.h"

int main()
{
    std::string path = "text.txt";

    FileAction::WriteNew(path, "hello world");

    std::string read = FileAction::Read(path);
    std::cout << read;
}

#include <headers/overlord.h>

int main(int argc, char* argv[])
{
    OverLord overlord;
    std::cout<<"START"<<std::endl;
    overlord.Run();
    std::cout<<"END"<<std::endl;
    return 0;
}
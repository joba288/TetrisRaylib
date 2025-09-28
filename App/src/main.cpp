#include <iostream>
#include "Application.h"
#include <raylib.h>


int main(void)
{
    Core::ApplicationSpec appSpec = {"Tetris", 1080, 720};
    Core::Application application(appSpec);

    application.Run();

}
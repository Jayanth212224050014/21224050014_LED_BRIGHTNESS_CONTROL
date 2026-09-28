#include "SwitchGlow.h"

int main(void)
{
    drive();
    Brightness_Init();

    while(1)
    {
        Brightness_Control();
    }
}

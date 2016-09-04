#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <3ds.h>

int main(int argc, char **argv)
{
    // Initialize services
    aptInit();
    gfxInitDefault();
    hidInit();
    gspLcdInit();
    
    consoleInit(GFX_TOP, NULL);
    
    bool isNew3DS = 0;
    APT_CheckNew3DS(&isNew3DS);
    if (isNew3DS)
    {
        u8 Screens = (u8)GSPLCD_GetVendor();
        printf("\nScreen Info:\n\n");
        switch ((Screens >> 4) & 0xF)
        {
            case 1:
                printf("Upper screen: IPS\n");
                break;
            case 0xC:
                printf("Upper screen: TN\n");
                break;
            default:
                printf("Upper screen: Unknown\n");
                break;
        }
         switch (Screens & 0xF)
        {
            case 1:
                printf("Lower screen: IPS\n");
                break;
            case 0xC:
                printf("Lower screen: TN\n");
                break;
            default:
                printf("Lower screen: Unknown\n");
                break;
        }
    }
    else
    {
        printf("\nCan't check O3DS Screen vendors.\n");
    }
    
    printf("\nPress START to exit.\n");
    
    while(aptMainLoop()) //Always have the main code loop in here
    {
        hidScanInput(); //Checks which keys are pressed

        u32 button = hidKeysDown(); // Checks which keys are up and which ones are down
        if (button & KEY_START)
        {
            break;
        }
    } 

    // Exit services
    aptExit();
    gfxExit();
    hidExit();
    gspLcdExit();
    return 0;
}

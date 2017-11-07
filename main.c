
#include <stdio.h>
#include <stdlib.h>

#include <3ds.h>

#include "common.h"

void wait_for_input(void)
{
   printf("\n\nPress Start.\n\n");
   fflush(stdout);

   while (aptMainLoop())
   {
      u32 kDown;

      hidScanInput();

      kDown = hidKeysDown();

      if (kDown & KEY_START)
         break;

      if (kDown & KEY_SELECT)
         exit(0);

      svcSleepThread(1000000);
   }
}

__attribute((aligned(0x1000)))
static u32 soc_buffer[0x100000 >> 2];

int main(int argc, char** argv)
{

   gfxInit(GSP_BGR8_OES,GSP_RGB565_OES,false);

   gfxSet3D(false);
   consoleInit(GFX_BOTTOM, NULL);
   socInit(soc_buffer, sizeof(soc_buffer));
//   osSetSpeedupEnable(true);

   printf("test\n");

   remoteinstall_receive_urls_network();
   wait_for_input();

   socExit();

   return 0;
}

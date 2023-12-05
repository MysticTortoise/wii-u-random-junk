#include <gfd.h>
#include <gx2/draw.h>
#include <gx2/shaders.h>
#include <gx2/mem.h>
#include <gx2/registers.h>
#include <gx2r/draw.h>
#include <gx2r/buffer.h>
#include <string.h>
#include <stdio.h>
#include <whb/file.h>
#include <whb/proc.h>
#include <whb/sdcard.h>
#include <whb/gfx.h>
#include <whb/log.h>
#include <whb/log_udp.h>

#include <coreinit/systeminfo.h>
#include <coreinit/thread.h>
#include <coreinit/time.h>
#include <coreinit/debug.h>

#include <romfs-wiiu.h>

#include <fstream>
#include <vector>

#include "camTablet.hpp"
#include "GameInput.hpp"
#include "TGAImport.hpp"
#include "numberSwapper.hpp"


// You're succeeding, Good job. :)

int main(int argc, char **argv)
{
   int result = 0;
    romfsInit();
    OSReport("main run\n");
   WHBLogUdpInit();
   WHBProcInit();
   InitializeGraphics();

    CamTabletRender MainRenderer = CamTabletRender();
    std::vector<Sprite> tvSprites{};

    Sprite tvSprite = Sprite("texture.tga");
    tvSprites.push_back(tvSprite);
    std::vector<Sprite> drcSprites{};
    drcSprites.push_back(Sprite("testimage.tga"));

    Input::WiiUGamepad mainGamepad;

   while (WHBProcIsRunning()) {

      
      mainGamepad.processInput();
      if(mainGamepad.buttons.at(Input::ButtonA).isPressed)
      {
         tvSprite.position.x += 0.01;
      }
      
      WHBGfxBeginRender();

      WHBGfxBeginRenderTV();
      MainRenderer.Render(tvSprites);
      WHBGfxFinishRenderTV();

      WHBGfxBeginRenderDRC();
      MainRenderer.Render(drcSprites);
      WHBGfxFinishRenderDRC();

      WHBGfxFinishRender();
   }

   WHBLogPrintf("Exiting...");
   romfsExit();
   WHBUnmountSdCard();
   WHBGfxShutdown();
   WHBProcShutdown();
   WHBLogUdpDeinit();
   return 0;
}
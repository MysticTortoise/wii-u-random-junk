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
#include "TGAImport.hpp"
#include "numberSwapper.hpp"



GX2Texture* s_texture = nullptr;
GX2Sampler s_sampler = {};

alignas(0x100) uint32_t s_timePSUniformBlock[4] = { };
int64_t launchTime;




int main(int argc, char **argv)
{
   int result = 0;
    romfsInit();
    OSReport("main run\n");
    // So ^^ gets run but VV doesn't... what the shit.
    OSReport("INIT ALL SHIT\n");
   WHBLogUdpInit();
   WHBProcInit();
   OSReport("INIT GRAPHIX\n");
   InitializeGraphics();
   OSReport("GRAPHIX DONE DOING THINGy\n");

    CamTabletRender *MainRenderer = new CamTabletRender();
    std::vector<Sprite*> sprites{};
    sprites.push_back(new Sprite("texture.tga"));

   OSReport("OK MAIN LOOP NOW\n");
   while (WHBProcIsRunning()) {

        WHBGfxBeginRender();
        OSReport("RENDER PLS\n");

        WHBGfxBeginRenderTV();
        MainRenderer->Render(sprites);
        WHBGfxFinishRenderTV();
        OSReport("RENDER DRC PLS\n");

        WHBGfxBeginRenderDRC();
        //MainRenderer->Render(sprites);
        WHBGfxFinishRenderDRC();

         OSReport("RENDER DONE PLS\n");

        WHBGfxFinishRender();
   }

   WHBLogPrintf("Exiting...");
   delete MainRenderer;
   romfsExit();
   WHBUnmountSdCard();
   WHBGfxShutdown();
   WHBProcShutdown();
   WHBLogUdpDeinit();
   return 0;
}
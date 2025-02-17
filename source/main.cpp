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

#include "Scene.hpp"
#include "GameObject.hpp"
#include "GameStateManager.hpp"

#include "TransformComponent.hpp"
#include "datatypes.hpp"
#include "HelperStandard.hpp"

#include "SceneList.hpp"


// You're succeeding, Good job. :)

int main(int argc, char **argv)
{
   int result = 0;
   romfsInit();
  // OSReport("main run\n");
   WHBLogUdpInit();
   WHBProcInit();
   InitializeGraphics();


   GameStateManager::LoadSceneFromFile("SceneDefs/testScene.json");

   while (WHBProcIsRunning()) {
      GameStateManager::currentScene->Update();
      GameStateManager::currentScene->Draw();
   }


   GameStateManager::EndCurrentSceneScene();


   WHBLogPrintf("Exiting...");
   romfsExit();
   WHBUnmountSdCard();
   WHBGfxShutdown();
   WHBProcShutdown();
   WHBLogUdpDeinit();
   return 0;
}
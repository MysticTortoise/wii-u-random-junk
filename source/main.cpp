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
#include "HelperStandard.hpp"
#include "EngineCore/Scene.hpp"
#include "MainRendererComponent.hpp"
#include "SpriteComponent.hpp"
#include "TransformComponent.hpp"


// You're succeeding, Good job. :)

int main(int argc, char **argv)
{
   int result = 0;
    romfsInit();
    OSReport("main run\n");
   WHBLogUdpInit();
   WHBProcInit();
   InitializeGraphics();

   
   GameScene* testScene = new GameScene();
   GameObject* mainRenderObject = testScene->CreateGameobject();
   print("OK graphix");
   MainRendererComponent* mainRenderComp = (MainRendererComponent*)mainRenderObject->AddComponent<MainRendererComponent>();
   Camera2DComponent* cameraComp = (Camera2DComponent*)mainRenderObject->AddComponent<Camera2DComponent>();
   mainRenderComp->camera = (Camera2DComponent*)mainRenderObject->GetComponent<Camera2DComponent>();

   GameObject* spriteObject = testScene->CreateGameobject();
   print("OK sprites");
   SpriteComponent* spriteComp = new SpriteComponent("texture.tga");
   spriteObject->AddComponent(spriteComp);
   spriteComp->linkedRenderer = mainRenderComp;
   print("shit penis fuck.");

   TransformComponent* spriteObjectTransform = (TransformComponent*)spriteObject->GetComponent<TransformComponent>();
   spriteObjectTransform->position = Vector2(0,0);
   spriteObjectTransform->size = Vector2(1,1);

   TransformComponent* camObjectTransform = (TransformComponent*)mainRenderObject->GetComponent<TransformComponent>();
   camObjectTransform->position = Vector2(0,0);
   camObjectTransform->size = Vector2(1,1);
   
   print("Ok Draw");

   while (WHBProcIsRunning()) {

      testScene->Draw();

   }

   WHBLogPrintf("Exiting...");
   romfsExit();
   WHBUnmountSdCard();
   WHBGfxShutdown();
   WHBProcShutdown();
   WHBLogUdpDeinit();
   return 0;
}

void __fastcall FUN_007af170(int param_1)

{
  Root *pRVar1;
  RenderSystem *pRVar2;
  
  FUN_007d21c0(*(undefined4 *)(param_1 + 0x178));
  FUN_007c3d60(0xff00ff00);
  FUN_007c3d60(0xff00ff00);
  FUN_007c3d60(0xff00ff00);
  if (*(undefined4 **)(param_1 + 0x178) != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)(param_1 + 0x178))(1);
  }
  *(undefined4 *)(param_1 + 0x178) = 0;
  if (DAT_009455ac != 0) {
    pRVar1 = Ogre::Root::getSingleton();
    pRVar2 = Ogre::Root::getRenderSystem(pRVar1);
    if (pRVar2 != (RenderSystem *)DAT_009455ac) {
      pRVar2 = (RenderSystem *)DAT_009455ac;
      pRVar1 = Ogre::Root::getSingleton();
      Ogre::Root::setRenderSystem(pRVar1,pRVar2);
      pRVar1 = Ogre::Root::getSingleton();
      Ogre::Root::saveConfig(pRVar1);
      FUN_0081e0c0("Exiting Game from graphics options changing renderer\n");
      FUN_00434170(9);
      DAT_00918328 = 0;
      FUN_007c9170(1);
                    /* WARNING: Subroutine does not return */
      exit(0);
    }
  }
  DAT_009455ac = 0;
  return;
}


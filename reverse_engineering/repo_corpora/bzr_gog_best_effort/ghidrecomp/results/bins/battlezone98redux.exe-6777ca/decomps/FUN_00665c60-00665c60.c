
void __fastcall FUN_00665c60(WindowEventListener *param_1)

{
  uint uVar1;
  CompositorManager *pCVar2;
  undefined4 uVar3;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0084e114;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *(undefined ***)param_1 = OgreFramework::vftable;
  local_8 = 1;
  if (*(undefined4 **)(param_1 + 0x48) != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)(param_1 + 0x48))(1,uVar1);
  }
  if (*(undefined4 **)(param_1 + 0x44) != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)(param_1 + 0x44))(1);
  }
  pCVar2 = Ogre::CompositorManager::getSingleton();
  (**(code **)(*(int *)pCVar2 + 0x40))();
  if (*(int *)(param_1 + 4) == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = FUN_00665d70(1);
  }
  local_8 = local_8 & 0xffffff00;
  Ogre::WindowEventListener::~WindowEventListener(param_1);
  local_8 = 0xffffffff;
  FUN_006666e0(uVar1,uVar3);
  ExceptionList = local_10;
  return;
}



void __fastcall FUN_007c64e0(FrameListener *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0086207b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *(undefined ***)param_1 = cUI_Parent::vftable;
  *(undefined ***)(param_1 + 4) = cUI_Parent::vftable;
  *(undefined ***)(param_1 + 8) = cUI_Parent::vftable;
  local_8 = 3;
  FUN_0081e820(" UI View Ended\n",uVar1);
  uVar2 = FUN_0081e660();
  FUN_004bc590(uVar2);
  if ((*(int *)(param_1 + 0x14) != 0) && (*(undefined4 **)(param_1 + 0x14) != (undefined4 *)0x0)) {
    (**(code **)**(undefined4 **)(param_1 + 0x14))(1);
  }
  FUN_007c6a30();
  FUN_00820fe0(1);
  FUN_0044d2a0();
  FUN_00663aa0();
  local_8._0_1_ = 2;
  FUN_0041fe20();
  local_8._0_1_ = 1;
  FUN_004b6430();
  local_8 = (uint)local_8._1_3_ << 8;
  Ogre::WindowEventListener::~WindowEventListener((WindowEventListener *)(param_1 + 4));
  local_8 = 0xffffffff;
  Ogre::FrameListener::~FrameListener(param_1);
  ExceptionList = local_10;
  return;
}



FrameListener * __thiscall
FUN_007c6360(FrameListener *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0086202b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  Ogre::FrameListener::FrameListener(param_1);
  local_8 = 0;
  Ogre::WindowEventListener::WindowEventListener((WindowEventListener *)(param_1 + 4));
  local_8._0_1_ = 1;
  FUN_004b6260(uVar1);
  local_8._0_1_ = 2;
  *(undefined ***)param_1 = cUI_Parent::vftable;
  *(undefined ***)(param_1 + 4) = cUI_Parent::vftable;
  *(undefined ***)(param_1 + 8) = cUI_Parent::vftable;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  param_1[0x19] = (FrameListener)0x0;
  param_1[0x24] = (FrameListener)0x0;
  param_1[0x26] = (FrameListener)0x0;
  param_1[0x27] = (FrameListener)0x0;
  vector<>();
  local_8 = CONCAT31(local_8._1_3_,3);
  param_1[0x25] = (FrameListener)0x1;
  param_1[0x18] = (FrameListener)0x0;
  FUN_0081e820(" UI View Started\n");
  uVar2 = FUN_0081e660();
  FUN_004bc590(uVar2);
  iVar3 = FUN_00572a70();
  if (iVar3 == 0) {
    FUN_004b6ef0();
  }
  FUN_0067dc80(DAT_00917580);
  FUN_004b6ec0();
  FUN_00820fe0(4);
  FUN_0044d2a0();
  FUN_00663aa0();
  FUN_007c65f0(param_2,param_3,param_4);
  FUN_007c6760();
  ExceptionList = local_10;
  return param_1;
}



void __fastcall FUN_007aa360(undefined4 *param_1)

{
  uint uVar1;
  int iVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008608db;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = cUI_Multiplayer_VehicleSelect::vftable;
  local_8 = 0;
  if (*(int *)(DAT_00920ea0 + 0x24) != 0) {
    iVar2 = Ogre::Viewport::getZOrder(*(Viewport **)(DAT_00920ea0 + 0x24));
    (**(code **)(*DAT_00920e80 + 0x40))(iVar2);
    *(undefined4 *)(DAT_00920ea0 + 0x24) = 0;
  }
  if (DAT_00945588 != (undefined4 *)0x0) {
    if (DAT_00945588 != (undefined4 *)0x0) {
      (**(code **)*DAT_00945588)(1,uVar1);
    }
    DAT_00945588 = (undefined4 *)0x0;
  }
  if (DAT_00920e98 != 0) {
    FUN_0067d090(DAT_00920e98);
    FUN_0067d0c0();
    DAT_00920e98 = 0;
  }
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  return;
}


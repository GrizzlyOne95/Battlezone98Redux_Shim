
void __thiscall FUN_00669b60(int param_1,undefined4 param_2,undefined1 param_3)

{
  char cVar1;
  uint uVar2;
  void *pvVar3;
  undefined4 local_38;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e825;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  pvVar3 = Ogre::AllocatedObject<class_Ogre::CategorisedAllocPolicy<0>_>::operator_new(0x70);
  local_8 = 0;
  if (pvVar3 == (void *)0x0) {
    local_38 = 0;
  }
  else {
    basic_string<>("i76FS");
    local_8 = CONCAT31(local_8._1_3_,1);
    local_38 = FUN_00667700(param_2,local_2c,param_3);
  }
  local_8 = 0xffffffff;
  if (pvVar3 != (void *)0x0) {
    ~basic_string<>(uVar2);
  }
  cVar1 = FUN_00427270(param_2,"./BZ_ASSETS");
  if (cVar1 != '\0') {
    *(undefined4 *)(param_1 + 4) = local_38;
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}


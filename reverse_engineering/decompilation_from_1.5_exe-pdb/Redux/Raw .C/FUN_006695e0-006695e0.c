
undefined4 FUN_006695e0(undefined4 param_1,undefined4 param_2,undefined1 param_3,undefined1 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 local_30 [12];
  undefined4 local_24;
  void *local_20;
  uint local_1c;
  undefined4 local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e732;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_1c = 0;
  local_20 = Ogre::StdAllocPolicy::allocateBytes(0x10,(char *)0x0,0,(char *)0x0);
  local_14 = forward<>(0x10,local_20,uVar1);
  local_8 = 1;
  if (local_14 == 0) {
    local_18 = 0;
  }
  else {
    local_18 = FUN_00669f20();
  }
  local_24 = local_18;
  local_8 = local_8 & 0xffffff00;
  FUN_0066e810(local_18,1);
  local_8 = 2;
  uVar2 = get();
  FUN_00668d80(param_2,param_3,param_4,0,uVar2);
  FUN_004498d0(local_30);
  local_1c = local_1c | 1;
  local_8 = local_8 & 0xffffff00;
  FUN_004499a0();
  ExceptionList = local_10;
  return param_1;
}


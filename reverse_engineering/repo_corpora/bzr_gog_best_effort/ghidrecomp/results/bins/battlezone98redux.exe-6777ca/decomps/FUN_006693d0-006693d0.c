
void FUN_006693d0(undefined4 param_1,undefined1 param_2,undefined1 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 local_44 [8];
  void *local_3c;
  int local_38;
  uint local_34;
  undefined4 local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e6da;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_34 = 0;
  local_14 = uVar1;
  local_3c = Ogre::StdAllocPolicy::allocateBytes(0x10,(char *)0x0,0,(char *)0x0);
  local_38 = forward<>(0x10,local_3c,uVar1);
  local_8 = 1;
  if (local_38 == 0) {
    local_30 = 0;
  }
  else {
    local_30 = FUN_00669f20();
  }
  local_8 = local_8 & 0xffffff00;
  FUN_0066e810(local_30,1);
  local_8 = 2;
  basic_string<>(&DAT_008922f0);
  local_8._0_1_ = 3;
  uVar2 = get();
  FUN_00668d80(local_2c,param_2,param_3,0,uVar2);
  local_8._0_1_ = 2;
  ~basic_string<>();
  FUN_004498d0(local_44);
  local_34 = local_34 | 1;
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_004499a0();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}


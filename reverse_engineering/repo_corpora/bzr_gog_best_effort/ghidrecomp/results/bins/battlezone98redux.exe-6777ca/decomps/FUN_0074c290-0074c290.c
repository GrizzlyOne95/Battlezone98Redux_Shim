
void FUN_0074c290(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844cc0;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  uVar2 = FUN_0073a9f0(local_44);
  local_8 = 0;
  uVar4 = uVar2;
  uVar3 = FUN_0045e1d0(local_2c,1,0xffffffff);
  local_8._0_1_ = 1;
  uVar4 = FUN_0074b350(uVar3,0,10,uVar1,uVar2,uVar3,uVar4);
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_8 = 0xffffffff;
  ~basic_string<>();
  get(uVar4);
  FUN_006c5760(uVar4);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}


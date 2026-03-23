
void FUN_007572a0(int param_1,int param_2,undefined1 param_3)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int local_68;
  undefined1 local_64 [80];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085c528;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  iVar2 = (param_2 - param_1) / 0x50;
  local_68 = iVar2 / 2;
  local_14 = uVar1;
  while (0 < local_68) {
    local_68 = local_68 + -1;
    uVar3 = FUN_00417780(local_68 * 0x50 + param_1,uVar1);
    FUN_00756b80(uVar3);
    local_8 = 0;
    uVar3 = FUN_00417780(local_64,param_3);
    FUN_007577b0(param_1,local_68,iVar2,uVar3);
    local_8 = 0xffffffff;
    FUN_007538f0();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}


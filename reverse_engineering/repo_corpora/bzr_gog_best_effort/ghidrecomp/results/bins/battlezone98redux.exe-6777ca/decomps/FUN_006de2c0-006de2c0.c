
undefined4 __thiscall
FUN_006de2c0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  undefined1 local_24 [8];
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00853b90;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  piVar3 = (int *)(param_1 + 0x24);
  LOCK();
  iVar1 = *piVar3;
  *piVar3 = *piVar3;
  UNLOCK();
  if (iVar1 == 0) {
    local_14 = param_1;
    FUN_006c8ce0(param_1 + 0x38);
    local_8 = 0;
    FUN_006c8f00(uVar2);
    local_8._0_1_ = 1;
    local_18 = Statistics(param_3,local_24,param_4);
    FUN_006ad700(local_24);
    local_1c = local_18;
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_006c8f30();
    local_8 = 0xffffffff;
    FUN_006c8d50();
  }
  else {
    local_1c = 0;
  }
  ExceptionList = local_10;
  return local_1c;
}


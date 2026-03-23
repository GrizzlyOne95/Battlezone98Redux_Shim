
int __thiscall FUN_0071c6a0(undefined4 param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00857af1;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (param_2 == 0) {
    param_2 = allocate(1);
  }
  iVar2 = forward<>(0x20,param_2,uVar1);
  local_8 = 0;
  if (iVar2 != 0) {
    uVar3 = FUN_00417780(param_1);
    FUN_0071ec00(uVar3);
  }
  ExceptionList = local_10;
  return param_2;
}


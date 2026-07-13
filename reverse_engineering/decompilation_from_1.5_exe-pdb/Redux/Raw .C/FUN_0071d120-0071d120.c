
int __thiscall FUN_0071d120(undefined4 param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00857af1;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (param_2 == 0) {
    param_2 = FUN_00711b60(1);
  }
  iVar2 = forward<>(0x48,param_2,uVar1);
  local_8 = 0;
  if (iVar2 != 0) {
    FUN_0071f0d0(param_1);
  }
  ExceptionList = local_10;
  return param_2;
}


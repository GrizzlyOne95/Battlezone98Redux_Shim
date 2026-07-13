
int __thiscall FUN_00711650(undefined4 param_1,int param_2)

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
    param_2 = allocate(1);
  }
  iVar2 = forward<>(0x28,param_2,uVar1);
  local_8 = 0;
  if (iVar2 != 0) {
    FUN_007131e0(param_1);
  }
  ExceptionList = local_10;
  return param_2;
}



void __thiscall FUN_0044e260(undefined4 param_1,undefined4 *param_2,undefined4 param_3)

{
  uint uVar1;
  int iVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084688b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = 0;
  }
  iVar2 = FUN_0044dbb0(0x70,uVar1);
  local_8 = 0;
  if (iVar2 != 0) {
    FUN_0044dcd0(param_1,param_2,param_3);
  }
  ExceptionList = local_10;
  return;
}


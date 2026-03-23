
void __fastcall FUN_006d60e0(int param_1)

{
  int iVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00853498;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006d7310(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  iVar1 = param_1 + 0x1c;
  FUN_006cb470(iVar1);
  FUN_006d57b0(iVar1);
  *(undefined1 *)(param_1 + 0x20) = 0;
  FUN_006cb470();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}


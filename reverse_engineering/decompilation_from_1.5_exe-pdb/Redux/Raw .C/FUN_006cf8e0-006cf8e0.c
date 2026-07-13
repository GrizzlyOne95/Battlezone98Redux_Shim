
void __fastcall FUN_006cf8e0(undefined4 param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00852d28;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_006d3570(param_1);
  local_8 = 0xffffffff;
  FUN_006d11f0(uVar1);
  ExceptionList = local_10;
  return;
}


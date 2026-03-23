
undefined4 * __fastcall FUN_0075a1a0(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085c8b9;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = 0;
  FUN_0073a6b0(uVar1);
  *(undefined1 *)(param_1 + 6) = 0;
  *(undefined1 *)((int)param_1 + 0x19) = 0;
  *(undefined1 *)((int)param_1 + 0x1a) = 0;
  *(undefined2 *)(param_1 + 7) = 0;
  FUN_006b29f0(2);
  FUN_006cb470();
  FUN_006cb470();
  FUN_006cb470();
  FUN_00421c40();
  local_8 = 0;
  param_1[0x21] = 0;
  param_1[0x22] = 0;
  param_1[0x24] = 0;
  param_1[0x25] = 0;
  vector<>();
  local_8 = CONCAT31(local_8._1_3_,1);
  vector<>();
  ExceptionList = local_10;
  return param_1;
}



undefined4 * __fastcall FUN_0056c250(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b2b8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0050b7e0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = MultDMMission::vftable;
  param_1[0x15] = MultDMMission::vftable;
  param_1[0x18] = 0;
  param_1[0x19] = 0;
  *(undefined1 *)(param_1 + 0x1b) = 0;
  param_1[0x1a] = 0;
  *(undefined1 *)((int)param_1 + 0x6d) = 0;
  FUN_005cb280(2,0);
  ExceptionList = local_10;
  return param_1;
}



undefined4 * __fastcall FUN_0045ca60(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008471e3;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_005d7300(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = AiMission::vftable;
  vector<>();
  local_8 = CONCAT31(local_8._1_3_,1);
  *(undefined1 *)((int)param_1 + 0x41) = 0;
  *(undefined1 *)((int)param_1 + 0x42) = 0;
  param_1[0x11] = 0xffffffff;
  *(undefined1 *)(param_1 + 0x12) = 0;
  param_1[0x13] = 0xffffffff;
  *(undefined1 *)(param_1 + 4) = 0;
  param_1[5] = 0;
  *(undefined1 *)(param_1 + 6) = 0;
  *(undefined4 *)((int)param_1 + 0x19) = 0;
  *(undefined4 *)((int)param_1 + 0x1d) = 0;
  *(undefined4 *)((int)param_1 + 0x21) = 0;
  *(undefined2 *)((int)param_1 + 0x25) = 0;
  FUN_006a3170();
  FUN_006a3780(2,1);
  ExceptionList = local_10;
  return param_1;
}


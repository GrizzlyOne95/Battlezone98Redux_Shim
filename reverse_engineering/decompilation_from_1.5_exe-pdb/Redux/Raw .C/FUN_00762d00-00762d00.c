
undefined4 * __thiscall FUN_00762d00(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085c8b9;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = *param_2;
  FUN_0073a740(param_2 + 2);
  *(undefined1 *)(param_1 + 6) = *(undefined1 *)(param_2 + 6);
  *(undefined1 *)((int)param_1 + 0x19) = *(undefined1 *)((int)param_2 + 0x19);
  *(undefined1 *)((int)param_1 + 0x1a) = *(undefined1 *)((int)param_2 + 0x1a);
  *(undefined2 *)(param_1 + 7) = *(undefined2 *)(param_2 + 7);
  uVar1 = param_2[9];
  param_1[8] = param_2[8];
  param_1[9] = uVar1;
  FUN_006cb4c0(param_2 + 10);
  FUN_006cb4c0(param_2 + 0x11);
  FUN_006cb4c0(param_2 + 0x18);
  FUN_00762f60(param_2 + 0x1f);
  local_8 = 0;
  param_1[0x21] = param_2[0x21];
  param_1[0x22] = param_2[0x22];
  param_1[0x24] = param_2[0x24];
  param_1[0x25] = param_2[0x25];
  FUN_00762e70(param_2 + 0x26);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00762fb0(param_2 + 0x29);
  ExceptionList = local_10;
  return param_1;
}



undefined4 * __fastcall FUN_004b7950(undefined4 *param_1)

{
  undefined4 *local_c;
  undefined4 *local_8;
  
  *param_1 = DistributedObject::vftable;
  *(undefined1 *)((int)param_1 + 0x61) = 0;
  *(undefined1 *)(param_1 + 2) = 0;
  *(undefined2 *)((int)param_1 + 0x62) = 0;
  *(undefined1 *)(param_1 + 0x1a) = 0;
  param_1[0x1b] = 0;
  param_1[0x1e] = 0;
  *(undefined1 *)(param_1 + 0x1c) = 0;
  param_1[0x1d] = 0x3f800000;
  param_1[0x17] = 0;
  *(undefined1 *)(param_1 + 0x18) = 0;
  local_c = param_1;
  local_8 = param_1;
  FUN_0041fe40(&local_c);
  return local_8;
}


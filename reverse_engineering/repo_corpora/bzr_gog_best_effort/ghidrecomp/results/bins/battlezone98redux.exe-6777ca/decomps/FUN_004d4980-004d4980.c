
undefined4 * __fastcall FUN_004d4980(undefined4 *param_1)

{
  undefined4 *local_24;
  int local_20;
  int local_1c;
  void *local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084762c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = GameFeature::vftable;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  *(undefined1 *)(param_1 + 9) = 0xff;
  *(byte *)((int)param_1 + 0x25) = *(byte *)((int)param_1 + 0x25) & 0xfe;
  *(byte *)((int)param_1 + 0x25) = *(byte *)((int)param_1 + 0x25) | 2;
  *(byte *)((int)param_1 + 0x25) = *(byte *)((int)param_1 + 0x25) | 4;
  *(byte *)((int)param_1 + 0x25) = *(byte *)((int)param_1 + 0x25) | 8;
  local_14 = param_1;
  if (DAT_00917a68 == 0) {
    local_18 = operator_new(0xc);
    local_8 = 0;
    if (local_18 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = vector<>();
    }
    local_20 = local_1c;
    DAT_00917a68 = local_1c;
  }
  local_8 = 0xffffffff;
  local_24 = local_14;
  FUN_0041fe40(&local_24);
  ExceptionList = local_10;
  return local_14;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * __thiscall FUN_006a0ae0(undefined4 *param_1,int param_2)

{
  char cVar1;
  undefined1 uVar2;
  uint uVar3;
  uint local_34;
  char *local_30;
  char *local_2c;
  int local_24;
  char *local_20;
  char *local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084fa38;
  local_10 = ExceptionList;
  uVar3 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_006a0de0(uVar3);
  local_8 = 0;
  *param_1 = UnitTypeAttachment::vftable;
  memset(param_1 + 1,0,0x88);
  local_2c = (char *)(param_2 + 0x30);
  local_1c = (char *)(param_1 + 6);
  do {
    cVar1 = *local_2c;
    *local_1c = cVar1;
    local_2c = local_2c + 1;
    local_1c = local_1c + 1;
  } while (cVar1 != '\0');
  *(undefined1 *)(param_1 + 8) = 0;
  local_30 = (char *)(param_1 + 6);
  local_20 = (char *)(param_1 + 0xe);
  do {
    cVar1 = *local_30;
    *local_20 = cVar1;
    local_30 = local_30 + 1;
    local_20 = local_20 + 1;
  } while (cVar1 != '\0');
  *(undefined2 *)((int)param_1 + 0x5a) = *(undefined2 *)(param_2 + 0x48);
  if (((*(int *)(param_2 + 0x1c) == 1) || (*(int *)(param_2 + 0x1c) == 6)) ||
     (*(int *)(param_2 + 0x1c) == 4)) {
    uVar2 = FUN_0046b550((int)(*(float *)(param_2 + 0x150) * 0.2),0xff,uVar3,param_1 + 0xe,
                         param_1 + 6);
    *(undefined1 *)(param_1 + 0x16) = uVar2;
  }
  else {
    *(undefined1 *)(param_1 + 0x16) = 0;
  }
  if (DAT_00931014 == 0) {
    _DAT_02c00a98 = _DAT_02c00a98 + 1;
    *(undefined2 *)((int)param_1 + 0x5e) = DAT_02c00a98;
  }
  else {
    *(undefined2 *)((int)param_1 + 0x5e) = DAT_02c00a90;
  }
  *(undefined2 *)((int)param_1 + 0x6a) = 0;
  *(undefined2 *)(param_1 + 0x1b) = 0;
  *(undefined2 *)((int)param_1 + 0x62) = 0;
  *(undefined2 *)(param_1 + 0x19) = 0;
  *(undefined2 *)(param_1 + 0x18) = 0;
  _DAT_02c00a8c = 1;
  _DAT_02c00a88 = 1;
  _DAT_02c00ec4 = 1;
  DAT_02c00ec8 = &DAT_02c00a88;
  param_1[2] = 1;
  param_1[3] = &DAT_02c00ec4;
  for (local_24 = 0; local_24 < 5; local_24 = local_24 + 1) {
    param_1[local_24 + 0x1e] = 0;
  }
  if (*(int *)(param_2 + 0x14) == 0x53434156) {
    param_1[0x1f] = *(undefined4 *)(param_2 + 0x5f0);
  }
  local_34 = (uint)(*(int *)(param_2 + 0x14) == 0x434e5354);
  param_1[0x1d] = param_1[0x1d] & 0xfffffffd | local_34 << 1;
  param_1[0x1d] = param_1[0x1d] & 0xfffffffe;
  ExceptionList = local_10;
  return param_1;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0083d3b0(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00865366;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 1;
  if ((DAT_00914cd8 & 1) == 0) {
    DAT_00914cd8 = DAT_00914cd8 | 1;
    _DAT_00914cc4 = &DAT_00914cc4;
    DAT_00914cd4 = 0;
    DAT_00914ccc = &DAT_00914cc4;
    DAT_00914cc8 = &DAT_00914cc4;
    _DAT_00914cd0 = 0;
  }
  DAT_00914cd4 = DAT_00914cd4 + -1;
  *param_1 = 0;
  param_1[3] = 0;
  *(undefined4 *)(param_1[1] + 8) = param_1[2];
  *(undefined4 *)(param_1[2] + 4) = param_1[1];
  if (((void *)param_1[0xf] != (void *)0x0) && (*(char *)(param_1 + 0x10) != '\0')) {
    _aligned_free((void *)param_1[0xf]);
    param_1[0xf] = 0;
  }
  FUN_0083d6a0(uVar1);
  if ((void *)param_1[0x12] != (void *)0x0) {
    operator_delete((void *)param_1[0x12]);
    param_1[0x12] = 0;
    param_1[0x13] = 0;
    param_1[0x14] = 0;
  }
  if (0xf < (uint)param_1[9]) {
    operator_delete((void *)param_1[4]);
  }
  param_1[9] = 0xf;
  param_1[8] = 0;
  *(undefined1 *)(param_1 + 4) = 0;
  ExceptionList = local_10;
  return;
}


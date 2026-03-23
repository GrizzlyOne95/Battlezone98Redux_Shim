
undefined4 * __thiscall FUN_0056d780(undefined4 *param_1,undefined4 param_2)

{
  uint uVar1;
  uint uVar2;
  uint local_1c;
  uint local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b438;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00461580(param_2,0);
  local_8 = 0;
  *param_1 = MultGEvent::vftable;
  param_1[0xfe] = 1;
  param_1[0x103] = 0;
  param_1[6] = 0;
  for (local_1c = 0; local_1c < 3; local_1c = local_1c + 1) {
    param_1[local_1c + 7] = 0;
  }
  for (local_18 = 0; local_18 < 0x1e; local_18 = local_18 + 1) {
    uVar2 = local_18 & 0x80000001;
    if ((int)uVar2 < 0) {
      uVar2 = (uVar2 - 1 | 0xfffffffe) + 1;
    }
    if (uVar2 == 0) {
      sprintf((char *)(param_1 + local_18 * 8 + 0xc),"repa%d",(int)local_18 / 2,uVar1);
    }
    else {
      sprintf((char *)(param_1 + local_18 * 8 + 0xc),"ammo%d",(int)local_18 / 2,uVar1);
    }
  }
  ExceptionList = local_10;
  return param_1;
}


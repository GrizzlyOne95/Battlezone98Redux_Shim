
void FUN_00692e70(undefined4 *param_1)

{
  int iVar1;
  int local_64;
  int local_60;
  int local_5c;
  undefined1 local_58 [80];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_64 = 0;
  local_60 = 0;
  local_5c = 0;
  FUN_006a3c40(local_58,*param_1);
  while( true ) {
    iVar1 = FUN_006a3c70(local_58);
    if (iVar1 == 0) break;
    local_64 = local_64 + *(int *)(iVar1 + 0xc);
    local_60 = local_60 + *(int *)(iVar1 + 0x10);
    local_5c = local_5c + 1;
  }
  if (local_5c == 0) {
    FUN_006a3aa0(local_58,*param_1);
    while( true ) {
      iVar1 = FUN_006a3b60(local_58);
      if (iVar1 == 0) break;
      local_64 = local_64 + *(int *)(iVar1 + 0x14);
      local_60 = local_60 + *(int *)(iVar1 + 0x18);
      local_5c = local_5c + 1;
    }
  }
  if (local_5c == 0) {
    param_1[0x91] = 0;
    param_1[0x92] = 0;
  }
  else {
    param_1[0x91] = local_64 / local_5c;
    param_1[0x92] = local_60 / local_5c;
    FUN_006a5fd0("AT Team %d Base Located at (%d, %d)\n",*param_1,param_1[0x91],param_1[0x92]);
  }
  FUN_0083e885();
  return;
}



void FUN_00472460(undefined4 param_1,int param_2)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined1 local_3c [12];
  int local_30;
  int local_2c;
  int local_28;
  undefined4 *local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008476b8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_005abab0(param_1,param_2);
  local_8 = 0;
  *local_24 = Armory::vftable;
  local_24[6] = Armory::vftable;
  local_2c = param_2 + 0x608;
  for (local_28 = 0; local_28 < 9; local_28 = local_28 + 1) {
    if (*(int *)(local_2c + local_28 * 4) != 0) {
      local_30 = *(int *)(*(int *)(local_2c + local_28 * 4) + 0x14);
      if (local_30 == 0x414d4d4f) {
        local_24[0xdc] = *(undefined4 *)(local_2c + local_28 * 4);
      }
      else if (local_30 == 0x524b4954) {
        local_24[0xdd] = *(undefined4 *)(local_2c + local_28 * 4);
      }
    }
  }
  local_24[0xde] = 0;
  puVar2 = (undefined4 *)FUN_00440000(local_3c,0,0,0,uVar1);
  local_20 = *puVar2;
  local_1c = puVar2[1];
  local_18 = puVar2[2];
  local_24[0xdf] = local_20;
  local_24[0xe0] = local_1c;
  local_24[0xe1] = local_18;
  if (local_24[0x68] != 0) {
    FUN_00472420(0,0);
  }
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}


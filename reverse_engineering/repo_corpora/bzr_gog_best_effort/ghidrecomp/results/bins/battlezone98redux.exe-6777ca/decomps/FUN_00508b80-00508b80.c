
void FUN_00508b80(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_94 [64];
  int local_54;
  int local_50;
  int local_4c;
  undefined4 local_48 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_4c = FUN_004ff820(param_1,1);
  if (local_4c != 0) {
    local_54 = FUN_004ff820(param_1,2);
    if (local_54 == 0) {
      local_50 = FUN_004ff7a0(param_1,2);
      if (local_50 != 0) {
        uVar3 = FUN_004ff7e0(param_1,local_50,1,local_4c);
        FUN_00820180(uVar3);
      }
    }
    else {
      puVar1 = (undefined4 *)FUN_0081fe60(local_94,local_4c,local_54);
      puVar2 = local_48;
      for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar2 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar2 = puVar2 + 1;
      }
      puVar2 = (undefined4 *)FUN_004ff840(param_1);
      puVar1 = local_48;
      for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar2 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar2 = puVar2 + 1;
      }
    }
  }
  FUN_0083e885();
  return;
}


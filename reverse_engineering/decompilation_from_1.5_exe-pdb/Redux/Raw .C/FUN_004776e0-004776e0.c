
void FUN_004776e0(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  float10 fVar3;
  undefined1 local_3c [12];
  int local_30;
  undefined4 local_2c;
  int local_28;
  float *local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_30 = param_1;
  local_2c = param_2;
  FUN_00477a70(&local_30);
  iVar1 = FUN_00416410();
  if (iVar1 == 1) {
    local_28 = FUN_00462630(local_24[1]);
    if ((param_1 == 0) || (local_28 == 0)) {
      local_14 = 0;
      local_c = 0x3f800000;
    }
    else {
      puVar2 = (undefined4 *)(**(code **)(*(int *)(local_28 + 0x18) + 0xc))();
      puVar2 = (undefined4 *)
               (**(code **)(*(int *)(param_1 + 0x18) + 0xc))(*puVar2,puVar2[1],puVar2[2]);
      puVar2 = (undefined4 *)FUN_004401a0(local_3c,*puVar2,puVar2[1],puVar2[2]);
      local_20 = *puVar2;
      local_1c = puVar2[1];
      local_18 = puVar2[2];
      local_14 = local_20;
      local_10 = local_1c;
      local_c = local_18;
    }
    fVar3 = (float10)FUN_0046e0a0(local_14,local_c);
    *local_24 = (float)fVar3;
  }
  FUN_0083e885();
  return;
}


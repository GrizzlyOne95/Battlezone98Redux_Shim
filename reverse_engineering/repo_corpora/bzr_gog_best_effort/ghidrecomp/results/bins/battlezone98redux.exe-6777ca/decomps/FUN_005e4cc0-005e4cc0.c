
void __fastcall FUN_005e4cc0(int *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined4 local_58;
  int local_54;
  undefined4 local_48 [10];
  undefined8 local_20;
  double local_18;
  undefined8 local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  *(uint *)(param_1[0x37] + 0x14) = *(uint *)(param_1[0x37] + 0x14) | 0x200;
  if (((*(uint *)(param_1[0x37] + 0x14) & 0x1000000) == 0) || (*(int *)(param_1[0x38] + 0x144) == 0)
     ) {
    local_54 = *(int *)(param_1[0x38] + 0x198);
  }
  else {
    local_54 = *(int *)(param_1[0x38] + 0x144);
  }
  puVar2 = (undefined4 *)(param_1[0x37] + 0x20);
  puVar3 = local_48;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  if (local_54 != 0) {
    iVar1 = FUN_004b0400();
    if (iVar1 == 0) {
      local_58 = 0;
    }
    else {
      local_58 = (**(code **)(*(int *)(iVar1 + 0x18) + 0x30))();
    }
    FUN_004cb7b0(local_48,local_58);
  }
  fVar4 = (float10)FUN_007855e0(local_20,local_10);
  if (local_18 < (double)((float)fVar4 + 5.0)) {
    FUN_007809d0();
  }
  (**(code **)(*param_1 + 0x10))();
  FUN_0083e885();
  return;
}


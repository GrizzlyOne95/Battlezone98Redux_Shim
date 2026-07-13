
void FUN_0045aae0(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_50 [16];
  uint local_40;
  undefined4 local_3c;
  int local_38;
  float local_34;
  uint local_2c;
  int local_28;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_00684ca0();
  if ((iVar1 != 0) && (iVar1 = FUN_004170c0(), iVar1 != 0)) {
    FUN_00447e20();
    while( true ) {
      iVar1 = FUN_00447e70();
      FUN_00447e50();
      iVar2 = FUN_00447e70();
      if (iVar1 == iVar2) break;
      local_38 = FUN_00447e70();
      local_28 = local_38;
      FUN_00447e90();
      puVar3 = (undefined4 *)
               FUN_006897e0(local_50,param_1,*(undefined8 *)(local_28 + 0xa8),
                            *(undefined8 *)(local_28 + 0xb0),*(undefined8 *)(local_28 + 0xb8));
      local_20 = *puVar3;
      local_1c = puVar3[1];
      local_18 = puVar3[2];
      local_14 = local_20;
      local_10 = local_1c;
      local_c = local_18;
      fVar4 = (float10)FUN_004428b0(&local_20,&local_20);
      local_34 = (float)fVar4;
      if ((local_34 <= *(float *)(local_24 + 0x1b4) * *(float *)(local_24 + 0x1b4)) &&
         ((*(float *)(local_24 + 0x1b8) <= 0.0 || (iVar1 = FUN_006895d0(), iVar1 < 1)))) {
        local_40 = get();
        for (local_2c = 0; local_2c < local_40; local_2c = local_2c + 1) {
          puVar3 = (undefined4 *)FUN_0045bb80();
          local_3c = *puVar3;
          FUN_0045a060(param_1,local_3c);
        }
      }
    }
  }
  FUN_0083e885();
  return;
}


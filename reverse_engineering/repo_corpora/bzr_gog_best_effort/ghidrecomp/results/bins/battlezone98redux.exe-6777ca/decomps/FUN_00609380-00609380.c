
void FUN_00609380(undefined4 *param_1,undefined4 *param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_2b8 [64];
  undefined1 local_278 [64];
  undefined1 local_238 [64];
  undefined1 local_1f8 [12];
  undefined1 local_1ec [12];
  undefined1 local_1e0 [12];
  undefined1 local_1d4 [12];
  uint local_1c8;
  undefined4 local_1c4;
  int local_1c0;
  undefined4 local_1bc;
  int local_1b8;
  int *local_1b4;
  int *local_1b0;
  int local_1ac;
  undefined4 local_1a8;
  undefined4 local_1a4;
  undefined4 local_1a0;
  undefined4 local_19c [16];
  undefined4 local_15c [16];
  undefined4 local_11c [16];
  undefined4 local_dc [16];
  undefined4 local_9c [16];
  undefined1 local_5c [12];
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1bc = FUN_00417ca0();
  local_1c4 = *(undefined4 *)(local_1c0 + 0xc);
  fVar4 = (float10)FUN_005ba130();
  puVar1 = (undefined4 *)FUN_0081ec40(local_238,(float)fVar4);
  puVar3 = local_19c;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar1 = local_19c;
  puVar3 = local_dc;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  *param_2 = 0;
  param_2[1] = 0;
  param_2[2] = 0;
  local_1b8 = 0;
  local_1c8 = FUN_00417f90();
  local_1b4 = (int *)0x0;
  for (local_1ac = 0; local_1ac < 5; local_1ac = local_1ac + 1) {
    if ((1 << ((byte)local_1ac & 0x1f) & local_1c8) != 0) {
      local_1b0 = (int *)FUN_00417f60(local_1ac);
      (**(code **)(*local_1b0 + 0x2c))(local_5c,param_3);
      local_1b4 = local_1b0 + 10;
      puVar1 = (undefined4 *)FUN_0081fe60(local_278,local_1b0[4] + 0x20,local_1b4);
      puVar3 = local_15c;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar3 = puVar3 + 1;
      }
      puVar1 = local_15c;
      puVar3 = local_9c;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar3 = puVar3 + 1;
      }
      puVar1 = (undefined4 *)FUN_008203f0(local_2b8,local_9c);
      puVar3 = local_11c;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar3 = puVar3 + 1;
      }
      puVar1 = local_11c;
      puVar3 = local_9c;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar3 = puVar3 + 1;
      }
      FUN_00820180(&local_1a8,local_5c,1,local_9c);
      puVar1 = (undefined4 *)FUN_00440300(local_1ec,&local_1a8,local_dc);
      local_1a8 = *puVar1;
      local_1a4 = puVar1[1];
      local_1a0 = puVar1[2];
      local_50 = local_1a8;
      local_4c = local_1a4;
      local_48 = local_1a0;
      puVar1 = (undefined4 *)
               FUN_00440130(local_1f8,*param_1,param_1[1],param_1[2],local_1a8,local_1a4,local_1a0);
      local_2c = *puVar1;
      local_28 = puVar1[1];
      local_24 = puVar1[2];
      *param_1 = local_2c;
      param_1[1] = local_28;
      param_1[2] = local_24;
      local_1b8 = local_1b8 + 1;
    }
  }
  if (1 < local_1b8) {
    puVar1 = (undefined4 *)
             FUN_004462d0(local_1d4,1.0 / (float)local_1b8,*param_1,param_1[1],param_1[2]);
    local_14 = *puVar1;
    local_10 = puVar1[1];
    local_c = puVar1[2];
    *param_1 = local_14;
    param_1[1] = local_10;
    param_1[2] = local_c;
  }
  if (local_1b4 != (int *)0x0) {
    puVar1 = (undefined4 *)FUN_00440210(local_1e0,param_1,local_1b4);
    local_20 = *puVar1;
    local_1c = puVar1[1];
    local_18 = puVar1[2];
    *param_2 = local_20;
    param_2[1] = local_1c;
    param_2[2] = local_18;
  }
  FUN_0083e885();
  return;
}


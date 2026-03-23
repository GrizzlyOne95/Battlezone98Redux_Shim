
void __thiscall FUN_0046d8c0(int param_1,float param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_cc [12];
  undefined1 local_c0 [12];
  undefined1 local_b4 [12];
  undefined1 local_a8 [12];
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  undefined4 *local_8c;
  int local_88;
  int local_84;
  undefined4 *local_80;
  int local_7c;
  undefined4 local_78 [16];
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
  local_7c = param_1;
  if (*(int *)(param_1 + 0xf0) == 0) {
    FUN_005bd060();
  }
  else {
    local_88 = FUN_004da060();
    if (local_88 == 0) {
      *(uint *)(*(int *)(local_7c + 0x14) + 0x14) =
           *(uint *)(*(int *)(local_7c + 0x14) + 0x14) | 0x200;
    }
    else {
      FUN_0045c4d0();
      puVar1 = (undefined4 *)FUN_0081fe60();
      puVar3 = local_78;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar3 = puVar3 + 1;
      }
      puVar1 = local_78;
      puVar3 = (undefined4 *)(*(int *)(local_7c + 0x14) + 0x20);
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar3 = puVar3 + 1;
      }
      local_84 = FUN_0045c490();
      local_8c = (undefined4 *)(local_84 + 0x18);
      local_94 = *(float *)(local_84 + 8);
      local_98 = *(float *)(*(int *)(local_7c + 0xc) + 0xd0) * param_2;
      if (local_94 <= local_98) {
        puVar1 = (undefined4 *)FUN_00440000(local_c0);
        local_20 = *puVar1;
        local_1c = puVar1[1];
        local_18 = puVar1[2];
        *local_8c = local_20;
        local_8c[1] = local_1c;
        local_8c[2] = local_18;
      }
      else {
        puVar1 = (undefined4 *)FUN_004462d0(local_a8,1.0 - local_98 / local_94);
        local_14 = *puVar1;
        local_10 = puVar1[1];
        local_c = puVar1[2];
        *local_8c = local_14;
        local_8c[1] = local_10;
        local_8c[2] = local_c;
      }
      local_80 = (undefined4 *)(local_84 + 0x24);
      fVar4 = (float10)FUN_0045c420();
      local_9c = (float)fVar4;
      local_90 = *(float *)(*(int *)(local_7c + 0xc) + 0xd4) * param_2;
      if (local_9c <= local_90) {
        puVar1 = (undefined4 *)FUN_00440000(local_b4);
        local_38 = *puVar1;
        local_34 = puVar1[1];
        local_30 = puVar1[2];
        *local_80 = local_38;
        local_80[1] = local_34;
        local_80[2] = local_30;
      }
      else {
        puVar1 = (undefined4 *)FUN_004462d0(local_cc,1.0 - local_90 / local_9c);
        local_2c = *puVar1;
        local_28 = puVar1[1];
        local_24 = puVar1[2];
        *local_80 = local_2c;
        local_80[1] = local_28;
        local_80[2] = local_24;
      }
      *(float *)(local_7c + 0x78) = *(float *)(local_7c + 0x78) - param_2;
      if (0.0 < *(float *)(local_7c + 0x78)) {
        *(uint *)(*(int *)(local_7c + 0x14) + 0x14) =
             *(uint *)(*(int *)(local_7c + 0x14) + 0x14) & 0xfffffdff;
      }
      else {
        *(uint *)(*(int *)(local_7c + 0x14) + 0x14) =
             *(uint *)(*(int *)(local_7c + 0x14) + 0x14) | 0x200;
      }
    }
  }
  FUN_0083e885();
  return;
}


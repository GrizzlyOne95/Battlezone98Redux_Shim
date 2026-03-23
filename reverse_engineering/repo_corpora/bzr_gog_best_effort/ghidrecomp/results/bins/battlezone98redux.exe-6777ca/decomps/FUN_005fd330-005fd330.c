
void FUN_005fd330(undefined4 *param_1,int param_2,int param_3,float param_4)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  undefined1 local_a0 [12];
  undefined1 local_94 [12];
  undefined1 local_88 [12];
  undefined1 local_7c [12];
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
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
  puVar1 = (undefined4 *)(**(code **)(*(int *)(param_3 + 0x18) + 0xc))();
  puVar1 = (undefined4 *)(**(code **)(*(int *)(param_2 + 0x18) + 0xc))(*puVar1,puVar1[1],puVar1[2]);
  puVar1 = (undefined4 *)FUN_004401a0(local_7c,*puVar1,puVar1[1],puVar1[2]);
  local_44 = *puVar1;
  local_40 = puVar1[1];
  local_3c = puVar1[2];
  local_20 = local_44;
  local_1c = local_40;
  local_18 = local_3c;
  uVar2 = FUN_0045c4d0();
  puVar1 = (undefined4 *)FUN_00439d80(local_94,uVar2);
  local_50 = *puVar1;
  local_4c = puVar1[1];
  local_48 = puVar1[2];
  local_14 = local_50;
  local_10 = local_4c;
  local_c = local_48;
  fVar4 = (float10)FUN_004428b0(&local_50,&local_44);
  local_58 = (float)fVar4;
  fVar4 = (float10)FUN_00453f80(local_58);
  local_70 = (float)fVar4;
  local_5c = local_70;
  iVar3 = FUN_00462400();
  if (*(float *)(iVar3 + 0xc) * 2.0 <= local_5c) {
    puVar1 = (undefined4 *)FUN_00440000(local_a0,0,0,0);
    local_2c = *puVar1;
    local_28 = puVar1[1];
    local_24 = puVar1[2];
    *param_1 = local_2c;
    param_1[1] = local_28;
    param_1[2] = local_24;
  }
  else {
    fVar4 = (float10)FUN_00453f80(local_58,0x3f000000);
    local_68 = (float)fVar4;
    local_60 = local_68 * 0.5;
    iVar3 = FUN_00462400();
    fVar4 = (float10)FUN_00456080(1.0 - local_60 / *(float *)(iVar3 + 0xc));
    local_54 = (float)fVar4;
    if (local_58 < 0.0) {
      local_54 = -local_54;
    }
    fVar4 = (float10)FUN_00822da0();
    local_6c = (float)fVar4;
    iVar3 = FUN_004b75c0();
    fVar4 = (float10)FUN_00822970((float)iVar3 + local_6c * 0.75 + 72.86);
    local_64 = (float)fVar4;
    local_54 = local_64 + local_54;
    puVar1 = (undefined4 *)FUN_004462d0(local_88,param_4 * local_54,local_50,local_4c,local_48);
    local_38 = *puVar1;
    local_34 = puVar1[1];
    local_30 = puVar1[2];
    *param_1 = local_38;
    param_1[1] = local_34;
    param_1[2] = local_30;
  }
  FUN_0083e885();
  return;
}


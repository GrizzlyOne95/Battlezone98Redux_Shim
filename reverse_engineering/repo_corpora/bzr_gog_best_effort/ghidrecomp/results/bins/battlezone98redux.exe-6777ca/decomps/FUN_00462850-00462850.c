
void FUN_00462850(int param_1,int param_2,float param_3,undefined4 param_4,float param_5)

{
  undefined4 *puVar1;
  float *pfVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_68 [12];
  undefined1 local_5c [12];
  float local_50;
  float local_4c;
  float local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar1 = (undefined4 *)(**(code **)(*(int *)(param_1 + 0x18) + 0xc))();
  local_38 = *puVar1;
  local_34 = puVar1[1];
  local_30 = puVar1[2];
  puVar1 = (undefined4 *)(**(code **)(*(int *)(param_2 + 0x18) + 0xc))();
  local_44 = *puVar1;
  local_40 = puVar1[1];
  local_3c = puVar1[2];
  pfVar2 = (float *)FUN_004401a0(local_5c,local_44,local_40,local_3c,local_38,local_34,local_30);
  local_2c = *pfVar2;
  local_28 = pfVar2[1];
  local_24 = pfVar2[2];
  local_14 = local_2c;
  local_10 = local_28;
  local_c = local_24;
  uVar3 = FUN_0045c4d0();
  pfVar2 = (float *)FUN_00440300(local_68,&local_14,uVar3);
  local_20 = *pfVar2;
  local_1c = pfVar2[1];
  local_18 = pfVar2[2];
  local_14 = local_20;
  local_10 = local_1c;
  local_c = local_18;
  if ((0.0 <= local_18) && (local_18 <= param_3)) {
    iVar4 = FUN_00462400();
    param_5 = *(float *)(iVar4 + 0xc) * param_5;
    local_48 = param_5 * param_5;
    local_4c = local_14 * local_14 + local_10 * local_10;
    if (local_48 <= local_4c) {
      local_50 = local_c * local_c + local_4c;
    }
  }
  FUN_0083e885();
  return;
}



void FUN_004447e0(int param_1,int param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  float10 fVar2;
  undefined1 local_70 [12];
  undefined1 local_64 [12];
  undefined1 local_58 [12];
  float local_4c;
  uint local_48;
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
  puVar1 = (undefined4 *)
           ((uint)*(ushort *)(*(int *)(param_1 + 0x14) + -2 + *(int *)(param_1 + 0x10) * 2) * 0xc +
           param_2);
  local_38 = *puVar1;
  local_34 = puVar1[1];
  local_30 = puVar1[2];
  for (local_48 = 0; local_48 < *(uint *)(param_1 + 0x10); local_48 = local_48 + 1) {
    puVar1 = (undefined4 *)
             ((uint)*(ushort *)(*(int *)(param_1 + 0x14) + local_48 * 2) * 0xc + param_2);
    local_44 = *puVar1;
    local_40 = puVar1[1];
    local_3c = puVar1[2];
    puVar1 = (undefined4 *)
             FUN_004401a0(local_64,local_44,local_40,local_3c,local_38,local_34,local_30);
    local_14 = *puVar1;
    local_10 = puVar1[1];
    local_c = puVar1[2];
    puVar1 = (undefined4 *)
             FUN_004401a0(local_58,*param_3,param_3[1],param_3[2],local_38,local_34,local_30);
    local_20 = *puVar1;
    local_1c = puVar1[1];
    local_18 = puVar1[2];
    puVar1 = (undefined4 *)FUN_004440d0(local_70,&local_20,&local_14);
    local_2c = *puVar1;
    local_28 = puVar1[1];
    local_24 = puVar1[2];
    fVar2 = (float10)FUN_004428b0(&local_2c,param_1);
    local_4c = (float)fVar2;
    if (local_4c < 0.0) break;
    local_38 = local_44;
    local_34 = local_40;
    local_30 = local_3c;
  }
  FUN_0083e885();
  return;
}


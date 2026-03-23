
void __thiscall FUN_004ca8f0(int param_1,undefined4 param_2)

{
  undefined8 *puVar1;
  float *pfVar2;
  int iVar3;
  undefined1 local_9c [12];
  undefined4 local_90;
  undefined4 local_8c;
  int local_88;
  float local_84;
  undefined4 local_80;
  undefined4 uStack_7c;
  undefined4 local_78;
  undefined4 uStack_74;
  undefined4 local_70;
  undefined4 uStack_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
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
  local_88 = param_1;
  if ((0 < *(int *)(*(int *)(param_1 + 8) + 0x30)) &&
     (local_84 = *(float *)(*(int *)(param_1 + 0xc) + 0xac), local_84 != 0.0)) {
    puVar1 = (undefined8 *)FUN_0081fd40();
    local_80 = *(undefined4 *)puVar1;
    uStack_7c = *(undefined4 *)((int)puVar1 + 4);
    local_78 = *(undefined4 *)(puVar1 + 1);
    uStack_74 = *(undefined4 *)((int)puVar1 + 0xc);
    local_70 = *(undefined4 *)(puVar1 + 2);
    uStack_6c = *(undefined4 *)((int)puVar1 + 0x14);
    local_68 = local_80;
    local_64 = uStack_7c;
    local_60 = local_78;
    local_5c = uStack_74;
    local_58 = local_70;
    local_54 = uStack_6c;
    pfVar2 = (float *)FUN_006897e0(local_9c,param_2,*puVar1,puVar1[1],puVar1[2]);
    local_50 = *pfVar2;
    local_4c = pfVar2[1];
    local_48 = pfVar2[2];
    local_44 = local_50;
    local_40 = local_4c;
    local_3c = local_48;
    iVar3 = FUN_006895d0();
    if (iVar3 < 1) {
      FUN_0049bf10();
      local_90 = FUN_0083f040();
      local_38 = local_44 - local_84;
      local_34 = local_40 + local_84;
      local_30 = local_3c;
      local_2c = local_44 + local_84;
      local_28 = local_40 + local_84;
      local_24 = local_3c;
      local_20 = local_44 + local_84;
      local_1c = local_40 - local_84;
      local_18 = local_3c;
      local_14 = local_44 - local_84;
      local_10 = local_40 - local_84;
      local_c = local_3c;
      local_8c = DAT_00920ef4;
      DAT_00920ef4 = local_3c - local_84;
      FUN_0068d2f0(param_2,local_90,&local_38,4);
      DAT_00920ef4 = (float)local_8c;
    }
  }
  FUN_0083e885();
  return;
}


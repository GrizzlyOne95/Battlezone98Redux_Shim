
void __fastcall FUN_00602420(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  float10 fVar3;
  undefined1 local_a8 [12];
  undefined1 local_9c [12];
  undefined1 local_90 [12];
  undefined1 local_84 [12];
  undefined1 local_78 [12];
  float local_6c;
  float *local_68;
  int local_64;
  int local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
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
  local_68 = (float *)(*(int *)(*(int *)(param_1 + 0x10) + 0x230) + 0xc4);
  local_60 = param_1;
  local_64 = FUN_0045c490();
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  if (4.0 <= *(float *)(local_60 + 0x98)) {
    cVar1 = (**(code **)(**(int **)(local_60 + 0x10) + 0x6c))();
    if (cVar1 != '\0') {
      puVar2 = (undefined4 *)FUN_005fd5f0(local_9c);
      local_5c = *puVar2;
      local_58 = puVar2[1];
      local_54 = puVar2[2];
      local_14 = local_5c;
      local_10 = local_58;
      local_c = local_54;
      fVar3 = (float10)FUN_00822d60();
      local_6c = (float)fVar3;
      puVar2 = (undefined4 *)FUN_004401a0(local_78,local_5c,local_58,local_54);
      local_50 = *puVar2;
      local_4c = puVar2[1];
      local_48 = puVar2[2];
      puVar2 = (undefined4 *)
               FUN_00439d00(local_84,*(undefined4 *)(local_60 + 0x128),
                            *(undefined4 *)(local_60 + 300),*(undefined4 *)(local_60 + 0x130),
                            local_6c * 2.0);
      local_2c = *puVar2;
      local_28 = puVar2[1];
      local_24 = puVar2[2];
      *(undefined4 *)(local_60 + 0x128) = local_2c;
      *(undefined4 *)(local_60 + 300) = local_28;
      *(undefined4 *)(local_60 + 0x130) = local_24;
      puVar2 = (undefined4 *)FUN_00440130(local_90,local_44,local_40,local_3c);
      local_44 = *puVar2;
      local_40 = puVar2[1];
      local_3c = puVar2[2];
      local_38 = local_44;
      local_34 = local_40;
      local_30 = local_3c;
    }
  }
  if (0.01 < *(float *)(local_64 + 8)) {
    puVar2 = (undefined4 *)FUN_00439d00(local_a8,local_44,local_40,local_3c,0xc0800000);
    local_44 = *puVar2;
    local_40 = puVar2[1];
    local_3c = puVar2[2];
    local_20 = local_44;
    local_1c = local_40;
    local_18 = local_3c;
  }
  FUN_00606f70();
  fVar3 = (float10)FUN_00447ed0();
  *local_68 = (float)fVar3;
  local_68[4] = 0.0;
  FUN_0083e885();
  return;
}


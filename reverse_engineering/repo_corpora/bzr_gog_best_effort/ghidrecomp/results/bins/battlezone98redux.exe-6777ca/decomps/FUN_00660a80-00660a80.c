
void __thiscall FUN_00660a80(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int local_58;
  float *local_4c;
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
  for (local_4c = (float *)(param_1 + 0x28); local_4c < *(float **)(param_1 + 0x1a8);
      local_4c = local_4c + 6) {
    local_48 = *local_4c;
    local_44 = local_4c[1];
    local_40 = local_4c[2];
    local_3c = local_4c[3];
    FUN_00820180(&local_48,&local_48,1,param_2 + 0x40);
    iVar2 = FUN_006895d0(param_2,&local_48,local_3c);
    if (iVar2 < 1) {
      FUN_0049bf10((float)*(int *)(param_1 + 0x1b8) * local_4c[4]);
      iVar2 = FUN_0083f040();
      uVar1 = DAT_00920ef4;
      if (*(char *)(local_4c + 5) == '\0') {
        local_58 = *(int *)(param_1 + 0x1b0);
      }
      else {
        local_58 = *(int *)(param_1 + 0x1ac);
      }
      local_38 = local_48 - local_3c;
      local_34 = local_44 + local_3c;
      local_30 = local_40;
      local_2c = local_48 + local_3c;
      local_28 = local_44 + local_3c;
      local_24 = local_40;
      local_20 = local_48 + local_3c;
      local_1c = local_44 - local_3c;
      local_18 = local_40;
      local_14 = local_48 - local_3c;
      local_10 = local_44 - local_3c;
      local_c = local_40;
      DAT_00920ef4 = local_40 - local_3c;
      FUN_0068d2f0(param_2,iVar2 + local_58,&local_38,4);
      DAT_00920ef4 = (float)uVar1;
    }
  }
  FUN_0083e885();
  return;
}



void __thiscall FUN_00480f40(int param_1,float *param_2,double *param_3)

{
  char cVar1;
  float *pfVar2;
  int iVar3;
  undefined1 local_98 [44];
  undefined4 *local_6c;
  int local_68;
  int local_64;
  float local_60;
  int *local_5c;
  int local_58;
  int local_54;
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
  local_54 = param_1;
  if (0.0 < *param_2) {
    local_60 = 1.0 / *param_2;
    local_20 = (float)*(double *)(*(int *)(param_1 + 0x14) + 0x48);
    local_1c = (float)*(double *)(*(int *)(param_1 + 0x14) + 0x50);
    local_18 = (float)*(double *)(*(int *)(param_1 + 0x14) + 0x58);
    local_14 = (float)(*param_3 - *(double *)(*(int *)(param_1 + 0x14) + 0x48)) * local_60;
    local_10 = (float)(param_3[1] - *(double *)(*(int *)(param_1 + 0x14) + 0x50)) * local_60;
    local_c = (float)(param_3[2] - *(double *)(*(int *)(param_1 + 0x14) + 0x58)) * local_60;
    pfVar2 = (float *)FUN_004801a0();
    local_50 = *pfVar2;
    local_4c = pfVar2[1];
    local_48 = pfVar2[2];
    local_44 = pfVar2[3];
    local_40 = pfVar2[4];
    local_3c = pfVar2[5];
    local_68 = 0;
    local_38 = local_50;
    local_34 = local_4c;
    local_30 = local_48;
    local_2c = local_44;
    local_28 = local_40;
    local_24 = local_3c;
    FUN_005b2950((double)local_50,(double)local_48,(double)local_44,(double)local_3c,local_98);
    while (cVar1 = FUN_00462710(&local_6c), cVar1 != '\0') {
      local_58 = FUN_004da060(*local_6c);
      if (local_58 != 0) {
        local_5c = (int *)(**(code **)(*(int *)(local_58 + 0x18) + 0x2c))();
        local_64 = *local_5c;
        if ((*(char *)(local_54 + 0xe0) == '\0') || (*(int *)(local_54 + 0xd8) != local_64)) {
          iVar3 = FUN_00442fd0();
          if ((iVar3 != 0) && (cVar1 = FUN_00480a30(), cVar1 != '\0')) {
            local_68 = local_64;
            *param_3 = (double)(*param_2 * local_14 + local_20);
            param_3[1] = (double)(*param_2 * local_10 + local_1c);
            param_3[2] = (double)(*param_2 * local_c + local_18);
          }
        }
        else {
          iVar3 = FUN_00442fd0();
          if (iVar3 == 0) {
            *(undefined1 *)(local_54 + 0xe0) = 0;
          }
        }
      }
    }
  }
  FUN_0083e885();
  return;
}


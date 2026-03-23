
void FUN_005d5d70(float *param_1,int *param_2)

{
  char cVar1;
  float *pfVar2;
  float10 fVar3;
  undefined1 local_74 [12];
  undefined4 local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  int local_30;
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
  cVar1 = (**(code **)(*param_2 + 0x14))();
  if (cVar1 == '\0') {
    FUN_0048f5e0(param_1,param_2);
  }
  else {
    local_68 = *(undefined4 *)(param_2[0x8c] + 0xfc);
    pfVar2 = (float *)FUN_0062e120(local_74,local_68);
    local_2c = *pfVar2;
    local_28 = pfVar2[1];
    local_24 = pfVar2[2];
    local_14 = local_2c;
    local_10 = local_28;
    local_c = local_24;
    if (((*(uint *)(*(int *)(local_30 + 0x18) + 0x14) & 0x30) != 0) &&
       (*(int *)(local_30 + 0xc) != 0)) {
      fVar3 = (float10)FUN_004624d0();
      local_64 = (float)fVar3;
      if (0.1 < local_64) {
        pfVar2 = (float *)FUN_004624b0();
        local_20 = *pfVar2;
        local_1c = pfVar2[1];
        local_18 = pfVar2[2];
        local_5c = *(float *)(*(int *)(local_30 + 0xc) + 0x54);
        local_14 = local_14 - (float)*(double *)(local_30 + 0x50);
        local_10 = local_10 - (float)*(double *)(local_30 + 0x58);
        local_c = local_c - (float)*(double *)(local_30 + 0x60);
        local_40 = (local_20 * local_20 + local_1c * local_1c + local_18 * local_18) -
                   local_5c * local_5c;
        local_3c = local_14 * local_20 + local_10 * local_1c + local_c * local_18;
        local_44 = local_14 * local_14 + local_10 * local_10 + local_c * local_c;
        local_58 = local_3c * local_3c - local_40 * local_44;
        if (0.0 < local_58) {
          fVar3 = (float10)FUN_00417910(local_58);
          local_60 = (float)fVar3;
          if (local_3c <= 0.0) {
            local_48 = -local_3c - local_60;
          }
          else {
            local_48 = -(local_3c + local_60);
          }
          local_38 = local_48;
          if (0.0 < local_48 * local_40) {
            if (0.0 < local_48 * local_44) {
              local_50 = local_48 / local_40;
              local_54 = local_44 / local_48;
              local_4c = local_54;
              if (local_50 < local_54) {
                local_4c = local_50;
              }
              local_34 = local_4c;
            }
            else {
              local_34 = local_48 / local_40;
            }
          }
          else {
            local_34 = local_44 / local_48;
          }
        }
        else {
          local_34 = -local_3c / local_40;
          if (local_34 < 0.0) {
            local_34 = 0.0;
          }
        }
        local_14 = (float)((double)local_14 + *(double *)(local_30 + 0x50) +
                          (double)(local_34 * local_20));
        local_10 = (float)((double)local_10 + *(double *)(local_30 + 0x58) +
                          (double)(local_34 * local_1c));
        local_c = (float)((double)local_c + *(double *)(local_30 + 0x60) +
                         (double)(local_34 * local_18));
      }
    }
    *param_1 = local_14;
    param_1[1] = local_10;
    param_1[2] = local_c;
  }
  FUN_0083e885();
  return;
}


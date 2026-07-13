
void FUN_004fac70(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 float param_7)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 local_38;
  undefined4 local_34;
  uint local_28;
  char *local_24;
  int local_18;
  float *local_10;
  float local_c;
  float local_8;
  
  if ((((0 < param_6) && (*(int *)(param_1 + 0x430) < 0x100)) &&
      (*(int *)(param_1 + 0x1034) < 0x100)) &&
     ((*(int *)(param_1 + 0x430) + param_3 < 0x100 && (*(int *)(param_1 + 0x1034) + param_3 < 0xff))
     )) {
    iVar3 = rand();
    rand();
    local_28 = 1;
    local_10 = (float *)(param_1 + 0x434 + *(int *)(param_1 + 0x1034) * 0xc);
    local_24 = (char *)(param_1 + 0x30 + *(int *)(param_1 + 0x430) * 4);
    fVar1 = *(float *)(param_1 + 0x14);
    fVar2 = *(float *)(param_1 + 0x18);
    iVar4 = rand();
    uVar6 = iVar3 * 0x10000 + iVar4;
    rand();
    *local_10 = *(float *)(param_1 + 0x434 + param_2 * 0xc);
    local_10[1] = *(float *)(param_1 + 0x438 + param_2 * 0xc);
    local_10[2] = *(float *)(param_1 + 0x43c + param_2 * 0xc);
    iVar3 = *(int *)(param_1 + 0x1034);
    *(int *)(param_1 + 0x1034) = *(int *)(param_1 + 0x1034) + 1;
    for (local_18 = 1; local_18 < param_3; local_18 = local_18 + 1) {
      local_8 = 0.0;
      local_c = 0.0;
      if (param_4 < 1) {
        if (param_4 < 0) {
          local_8 = 0.0 - fVar1;
          local_c = 0.0 - fVar2;
        }
      }
      else {
        local_8 = fVar1 + 0.0;
        local_c = fVar2 + 0.0;
      }
      if ((param_4 < 1) || ((uVar6 & local_28) == 0)) {
        if ((param_4 < 0) && ((uVar6 & local_28) != 0)) {
          local_8 = local_8 - fVar1;
          local_c = local_c - fVar2;
        }
        else if ((param_4 == 0) && ((uVar6 & local_28) != 0)) {
          local_8 = local_8 + fVar1;
          local_c = local_c + fVar2;
        }
        else if ((param_4 == 0) && ((uVar6 & local_28) == 0)) {
          local_8 = local_8 - fVar1;
          local_c = local_c - fVar2;
        }
      }
      else {
        local_8 = local_8 + fVar1;
        local_c = local_c + fVar2;
      }
      local_10[3] = *local_10 + local_8;
      local_10[4] = local_10[1] - param_7;
      local_10[5] = local_10[2] + local_c;
      *local_24 = (char)*(undefined4 *)(param_1 + 0x1034) + -1;
      local_24[1] = *(char *)(param_1 + 0x1034);
      local_24[2] = '2';
      local_24[3] = DAT_009b7cb0;
      *(int *)(param_1 + 0x430) = *(int *)(param_1 + 0x430) + 1;
      *(int *)(param_1 + 0x1034) = *(int *)(param_1 + 0x1034) + 1;
      local_10 = local_10 + 3;
      local_24 = local_24 + 4;
      local_28 = local_28 << 1;
    }
    if (1 < param_6) {
      for (local_18 = 0; local_18 < param_5; local_18 = local_18 + 1) {
        uVar6 = rand();
        iVar4 = ((local_18 + 1) * param_3) / (param_5 + 1) + iVar3;
        iVar5 = param_3 - (iVar4 - iVar3);
        if (param_4 == 0) {
          if ((uVar6 & 1) == 0) {
            local_34 = 1;
          }
          else {
            local_34 = 0xffffffff;
          }
          local_38 = local_34;
        }
        else {
          local_38 = 0;
        }
        FUN_004fac70(param_1,iVar4,
                     ((int)(iVar5 + (iVar5 >> 0x1f & 3U)) >> 2) + ((int)(uVar6 * param_3) >> 0x10),
                     local_38,(uVar6 & 3) + 2,param_6 + -1,param_7);
      }
    }
  }
  return;
}



/* WARNING: Removing unreachable block (ram,0x0058f085) */
/* WARNING: Removing unreachable block (ram,0x0058f08e) */
/* WARNING: Removing unreachable block (ram,0x0058f107) */

void FUN_0058eec0(void)

{
  float fVar1;
  char cVar2;
  uint uVar3;
  float10 fVar4;
  int local_54 [2];
  float local_4c;
  float local_48;
  float local_44;
  undefined4 *local_40;
  undefined4 *local_3c;
  int local_38;
  float local_34;
  int local_30;
  float *local_2c;
  int local_28;
  float *local_24;
  int local_20;
  float local_1c;
  float local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084bdf8;
  local_10 = ExceptionList;
  uVar3 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_20 = DAT_00918144;
  local_3c = (undefined4 *)FUN_005111d0(0);
  local_40 = (undefined4 *)FUN_005111d0(1);
  DAT_02a13ca0 = FUN_0058d8a0(*local_3c,local_3c[1],0,DAT_00918154,uVar3);
  DAT_02a13c94 = FUN_0058d8a0(*local_40,local_40[1],0,DAT_00918164);
  *(undefined1 *)(DAT_02a13c94 + 0x1f) = 1;
  FUN_0058d230();
  local_8 = 0;
  local_18 = 0.0;
  fVar4 = (float10)FUN_0058d510(DAT_02a13ca0);
  local_1c = (float)fVar4;
  *(float *)(DAT_02a13ca0 + 0x2c) = local_18;
  *(undefined1 *)(DAT_02a13ca0 + 0x21) = 1;
  FUN_0058d2d0(DAT_02a13ca0,local_18 + local_1c);
  local_18 = 0.0;
  fVar4 = (float10)FUN_0058d510(DAT_02a13c94);
  local_1c = (float)fVar4;
  *(float *)(DAT_02a13c94 + 0x2c) = local_18;
  *(undefined1 *)(DAT_02a13c94 + 0x21) = 1;
  if (DAT_00917f8f != '\0') {
    FUN_0058d2d0(DAT_02a13c94,local_18 + local_1c);
  }
  DAT_02a13cb0 = 0;
  local_54[0] = 1;
  local_54[1] = 1;
  local_30 = 0;
  while( true ) {
    local_30 = local_30 + 1;
    if (499999 < local_30) {
      DAT_02a13cb0 = 0;
      goto LAB_0058f38e;
    }
    DAT_02a13cb0 = FUN_0058d290();
    if ((DAT_02a13cb0 == 0) ||
       (local_54[*(byte *)(DAT_02a13cb0 + 0x1f)] = local_54[*(byte *)(DAT_02a13cb0 + 0x1f)] + -1,
       *(char *)(DAT_02a13cb0 + 0x1d) != '\0')) goto LAB_0058f38e;
    FUN_0058deb0(DAT_02a13cb0);
    for (local_28 = FUN_0058d440(DAT_02a13cb0); -1 < local_28; local_28 = FUN_0058d470(local_28)) {
      local_14 = FUN_0058d4a0(local_28);
      fVar4 = (float10)FUN_0058bec0(*(undefined4 *)(DAT_02a13cb0 + 0x10));
      local_34 = (float)fVar4;
      fVar4 = (float10)FUN_0058d590(DAT_02a13cb0,local_14,local_34);
      local_44 = (float)fVar4;
      local_18 = local_44 + *(float *)(DAT_02a13cb0 + 0x2c);
      *(float *)(local_14 + 0x2c) = local_18;
      *(int *)(local_14 + 0x30) = DAT_02a13cb0;
      if (*(char *)(local_14 + 0x21) == '\0') {
        *(undefined1 *)(local_14 + 0x21) = 1;
        if (*(char *)(local_14 + 0x1d) == '\0') {
          fVar4 = (float10)FUN_0058d510(local_14);
          local_1c = (float)fVar4;
        }
        else {
          *(undefined1 *)(local_14 + 0x1f) = *(undefined1 *)(DAT_02a13cb0 + 0x1f);
          local_38 = *(int *)(local_14 + 0x34);
          fVar4 = (float10)FUN_0058bec0(*(undefined4 *)(local_14 + 0x10));
          local_34 = (float)fVar4;
          uVar3 = size();
          if (uVar3 < DAT_00918134) {
            fVar4 = (float10)FUN_0058d590(local_14,local_38,local_34);
            local_48 = (float)fVar4;
            local_1c = (float)fVar4 + *(float *)(local_38 + 0x2c);
          }
          else {
            fVar4 = (float10)FUN_0058d510(local_14);
            local_4c = (float)fVar4;
            local_1c = (float)fVar4 + *(float *)(local_38 + 0x2c);
          }
        }
        local_54[*(byte *)(local_14 + 0x1f)] = local_54[*(byte *)(local_14 + 0x1f)] + 1;
        FUN_0058d2d0(local_14,local_18 + local_1c);
      }
      else {
        fVar4 = (float10)FUN_0058d510(local_14);
        local_1c = (float)fVar4;
        cVar2 = FUN_0058d310(local_14);
        if (cVar2 == '\0') {
          FUN_0058d2d0(local_14,local_18 + local_1c);
          local_54[*(byte *)(local_14 + 0x1f)] = local_54[*(byte *)(local_14 + 0x1f)] + 1;
        }
        else {
          FUN_0058d330(local_14,local_18 + local_1c);
        }
      }
    }
    if (local_54[0] == 0) break;
    if (local_54[1] == 0) {
      DAT_02a13cb0 = 0;
LAB_0058f38e:
      if (DAT_02a13cb0 == 0) {
        *(undefined4 *)(local_20 + 0x10) = 1;
        local_2c = (float *)FUN_005111d0(0);
        local_24 = (float *)FUN_005111d0(1);
        *local_2c = *local_2c * DAT_02cc50e0;
        local_2c[1] = local_2c[1] * DAT_02cc50e0;
        *local_24 = *local_24 * DAT_02cc50e0;
        local_24[1] = local_24[1] * DAT_02cc50e0;
        *(undefined4 *)(local_20 + 0x14) = 0;
        fVar1 = local_24[1];
        *(float *)(local_20 + 0x18) = *local_24;
        *(float *)(local_20 + 0x1c) = fVar1;
      }
      else {
        FUN_0058e9b0(DAT_02a13cb0,local_20);
      }
      local_8 = 0xffffffff;
      FUN_0058d270();
      ExceptionList = local_10;
      return;
    }
  }
  DAT_02a13cb0 = 0;
  goto LAB_0058f38e;
}


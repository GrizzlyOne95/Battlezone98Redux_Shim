
void FUN_004693c0(int param_1,int param_2,int param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  float10 fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  int local_3c;
  float local_2c;
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  int local_14;
  
  if (DAT_00917380 != 0) {
    fVar4 = ((float)param_2 + 0.5) * DAT_02cc50e0;
    fVar5 = ((float)param_3 + 0.5) * DAT_02cc50e0;
    fVar6 = DAT_02cc50e0 * 0.5;
    local_20 = -1;
    local_2c = -3.4028235e+38;
    local_28 = *(undefined4 *)(&DAT_0260d150 + DAT_00917380 * 8);
    local_24 = *(undefined4 *)(&DAT_0260d154 + DAT_00917380 * 8);
    for (local_14 = 0; local_14 < DAT_00917380; local_14 = local_14 + 1) {
      uVar8 = FUN_00444e40((&DAT_0260d158)[local_14 * 2],(&DAT_0260d15c)[local_14 * 2],local_28,
                           local_24);
      uVar8 = FUN_004622a0(uVar8);
      uVar9 = FUN_00444e40(fVar4,fVar5,local_28,local_24);
      fVar3 = (float10)FUN_00444e70(uVar9,(int)((ulonglong)uVar8 >> 0x20),(uint)uVar8 ^ 0x80000000);
      fVar7 = (float)fVar3 - fVar6;
      if (0.0 < fVar7) {
        return;
      }
      if (local_2c < fVar7) {
        local_20 = local_14;
        local_2c = fVar7;
      }
      local_28 = (&DAT_0260d158)[local_14 * 2];
      local_24 = (&DAT_0260d15c)[local_14 * 2];
    }
    if (-fVar6 < local_2c) {
      local_3c = DAT_00917380;
      if (0 < local_20) {
        local_3c = local_20;
      }
      local_3c = local_3c + -1;
      puVar1 = &DAT_0260d158 + local_3c * 2;
      puVar2 = &DAT_0260d158 + local_20 * 2;
      uVar8 = FUN_00444e40(*puVar2,(&DAT_0260d15c)[local_20 * 2],*puVar1,
                           (&DAT_0260d15c)[local_3c * 2]);
      uVar9 = FUN_00444e40(fVar4,fVar5,*puVar1,(&DAT_0260d15c)[local_3c * 2]);
      fVar3 = (float10)FUN_00444e70(uVar9,uVar8);
      if (0.0 < (float)fVar3) {
        uVar8 = FUN_00444e40(*puVar1,(&DAT_0260d15c)[local_3c * 2],*puVar2,
                             (&DAT_0260d15c)[local_20 * 2]);
        uVar9 = FUN_00444e40(fVar4,fVar5,*puVar2,(&DAT_0260d15c)[local_20 * 2]);
        fVar3 = (float10)FUN_00444e70(uVar9,uVar8);
        if ((float)fVar3 <= 0.0) {
          uVar8 = FUN_00444e40(fVar4,fVar5,*puVar2,(&DAT_0260d15c)[local_20 * 2]);
          fVar3 = (float10)FUN_00444e70(uVar8,uVar8);
          if (fVar6 * fVar6 < (float)fVar3) {
            return;
          }
        }
      }
      else {
        uVar8 = FUN_00444e40(fVar4,fVar5,*puVar1,(&DAT_0260d15c)[local_3c * 2]);
        fVar3 = (float10)FUN_00444e70(uVar8,uVar8);
        if (fVar6 * fVar6 < (float)fVar3) {
          return;
        }
      }
    }
  }
  *(byte *)(DAT_0260d178 + param_1) = *(byte *)(DAT_0260d178 + param_1) | 0xb;
  return;
}


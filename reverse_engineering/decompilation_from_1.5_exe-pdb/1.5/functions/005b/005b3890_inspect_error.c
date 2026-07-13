/*
 * Entry: 005b3890
 * Name: inspect_error
 * Namespace: Global
 * Signature: int inspect_error(int param_1, int param_2, int param_3, int param_4, float * param_5, float * param_6, vorbis_info_floor1 * param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
inspect_error(int param_1,int param_2,int param_3,int param_4,float *param_5,float *param_6,
             vorbis_info_floor1 *param_7)

{
  float fVar1;
  float fVar2;
  int in_EAX;
  int iVar3;
  int iVar4;
  uint extraout_EAX;
  int iVar5;
  uint extraout_EAX_00;
  int in_ECX;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  float *pfVar11;
  int local_1c;
  int local_14;
  int local_10;
  
  uVar6 = in_ECX - param_2;
  iVar9 = param_1 - in_EAX;
  iVar3 = (int)uVar6 / iVar9;
  if ((int)uVar6 < 0) {
    iVar4 = iVar3 + -1;
  }
  else {
    iVar4 = iVar3 + 1;
  }
  local_1c = param_2;
  local_10 = 0;
  _ftol2_sse();
  if ((int)extraout_EAX < 0x400) {
    uVar7 = ((int)extraout_EAX < 0) - 1 & extraout_EAX;
  }
  else {
    uVar7 = 0x3ff;
  }
  uVar8 = iVar3 * iVar9 >> 0x1f;
  fVar2 = *(float *)(param_4 + in_EAX * 4) + param_5[0x116];
  fVar1 = *(float *)(param_3 + in_EAX * 4);
  iVar10 = (param_2 - uVar7) * (param_2 - uVar7);
  local_14 = 1;
  if (fVar1 < fVar2 != (fVar1 == fVar2)) {
    if ((float)param_2 + param_5[0x112] < (float)(int)uVar7) {
      return 1;
    }
    if ((float)(int)uVar7 < (float)param_2 - param_5[0x113]) {
      return 1;
    }
  }
  param_2 = in_EAX + 1;
  if (param_2 < param_1) {
    pfVar11 = (float *)(param_3 + param_2 * 4);
    do {
      local_10 = local_10 +
                 (((uVar6 ^ (int)uVar6 >> 0x1f) - ((int)uVar6 >> 0x1f)) -
                 ((iVar3 * iVar9 ^ uVar8) - uVar8));
      iVar5 = iVar3;
      if (iVar9 <= local_10) {
        local_10 = local_10 - iVar9;
        iVar5 = iVar4;
      }
      local_1c = local_1c + iVar5;
      _ftol2_sse();
      if ((int)extraout_EAX_00 < 0x400) {
        uVar7 = ((int)extraout_EAX_00 < 0) - 1 & extraout_EAX_00;
      }
      else {
        uVar7 = 0x3ff;
      }
      local_14 = local_14 + 1;
      iVar10 = iVar10 + (local_1c - uVar7) * (local_1c - uVar7);
      fVar1 = *(float *)((param_4 - param_3) + (int)pfVar11) + param_5[0x116];
      if ((*pfVar11 < fVar1 != (*pfVar11 == fVar1)) && (uVar7 != 0)) {
        if ((float)local_1c + param_5[0x112] < (float)(int)uVar7) {
          return 1;
        }
        if ((float)(int)uVar7 < (float)local_1c - param_5[0x113]) {
          return 1;
        }
      }
      param_2 = param_2 + 1;
      pfVar11 = pfVar11 + 1;
    } while (param_2 < param_1);
  }
  if (param_5[0x114] < (param_5[0x112] * param_5[0x112]) / (float)local_14) {
    return 0;
  }
  if (((param_5[0x113] * param_5[0x113]) / (float)local_14 <= param_5[0x114]) &&
     (param_5[0x114] < (float)(iVar10 / local_14))) {
    return 1;
  }
  return 0;
}

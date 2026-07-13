/*
 * Entry: 005b3330
 * Name: accumulate_fit
 * Namespace: Global
 * Signature: int accumulate_fit(float * param_1, float * param_2, int param_3, int param_4, lsfit_acc * param_5, int param_6, vorbis_info_floor1 * param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
accumulate_fit(float *param_1,float *param_2,int param_3,int param_4,lsfit_acc *param_5,int param_6,
              vorbis_info_floor1 *param_7)

{
  float fVar1;
  int in_EAX;
  int extraout_EAX;
  int iVar2;
  int iVar3;
  float *pfVar4;
  int *unaff_ESI;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  iVar2 = param_4;
  iVar3 = 0;
  param_4 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  local_8 = 0;
  memset();
  *unaff_ESI = in_EAX;
  unaff_ESI[1] = param_3;
  if (iVar2 <= param_3) {
    param_3 = iVar2 + -1;
  }
  if (in_EAX <= param_3) {
    pfVar4 = param_1 + in_EAX;
    do {
      _ftol2_sse();
      if (extraout_EAX < 0x400) {
        if ((-1 < extraout_EAX) && (iVar2 = extraout_EAX, extraout_EAX != 0)) goto LAB_005b33d1;
      }
      else {
        iVar2 = 0x3ff;
LAB_005b33d1:
        fVar1 = *(float *)(((int)param_2 - (int)param_1) + (int)pfVar4) + (float)param_5[0x13].xyb;
        if (*pfVar4 < fVar1 == (*pfVar4 == fVar1)) {
          local_18 = local_18 + iVar2;
          local_1c = local_1c + in_EAX;
          local_14 = local_14 + in_EAX * in_EAX;
          local_10 = local_10 + iVar2 * iVar2;
          local_c = local_c + iVar2 * in_EAX;
          local_8 = local_8 + 1;
        }
        else {
          local_2c = local_2c + iVar2;
          param_4 = param_4 + in_EAX;
          local_28 = local_28 + in_EAX * in_EAX;
          local_24 = local_24 + iVar2 * iVar2;
          local_20 = local_20 + iVar2 * in_EAX;
          iVar3 = iVar3 + 1;
        }
      }
      in_EAX = in_EAX + 1;
      pfVar4 = pfVar4 + 1;
    } while (in_EAX <= param_3);
  }
  unaff_ESI[2] = param_4;
  unaff_ESI[3] = local_2c;
  unaff_ESI[5] = local_24;
  unaff_ESI[4] = local_28;
  unaff_ESI[6] = local_20;
  unaff_ESI[9] = local_18;
  unaff_ESI[8] = local_1c;
  unaff_ESI[10] = local_14;
  unaff_ESI[0xc] = local_c;
  unaff_ESI[7] = iVar3;
  unaff_ESI[0xb] = local_10;
  unaff_ESI[0xd] = local_8;
  return iVar3;
}

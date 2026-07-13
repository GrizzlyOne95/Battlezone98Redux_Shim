/*
 * Entry: 005a5710
 * Name: _vp_offset_and_mix
 * Namespace: Global
 * Signature: void _vp_offset_and_mix(vorbis_look_psy * param_1, float * param_2, float * param_3, int param_4, float * param_5, float * param_6, float * param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
_vp_offset_and_mix(vorbis_look_psy *param_1,float *param_2,float *param_3,int param_4,float *param_5
                  ,float *param_6,float *param_7)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  float fVar5;
  vorbis_look_psy *pvVar6;
  float *pfVar7;
  float *pfVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  float *local_4c;
  float *local_48;
  float *local_40;
  int local_3c;
  
  pvVar6 = param_1;
  fVar1 = param_1->vi->tone_masteratt[param_4];
  iVar4 = param_1->n;
  fVar2 = param_1->m_val;
  local_3c = 0;
  if (3 < iVar4) {
    iVar9 = (int)param_6 - (int)param_3;
    local_48 = param_6 + 3;
    iVar10 = (int)param_6 - (int)param_5;
    local_4c = param_5 + 2;
    iVar11 = (iVar4 - 4U >> 2) + 1;
    local_3c = iVar11 * 4;
    local_40 = param_7;
    pfVar8 = param_3 + 1;
    do {
      fVar3 = *(float *)(-(int)param_3 + -4 + (int)pfVar8 + (int)pvVar6->noiseoffset[param_4]) +
              *(float *)(((int)param_2 - (int)param_7) + (int)local_40);
      if (pvVar6->vi->noisemaxsupp < fVar3) {
        fVar3 = pvVar6->vi->noisemaxsupp;
      }
      fVar5 = pfVar8[-1] + fVar1;
      if (pfVar8[-1] + fVar1 < fVar3) {
        fVar5 = fVar3;
      }
      local_4c[-2] = fVar5;
      if (param_4 == 1) {
        fVar5 = (fVar3 - *local_40) - -17.2;
        if (fVar3 - *local_40 <= -17.2) {
          param_1 = (vorbis_look_psy *)(1.0 - fVar5 * 0.0003 * fVar2);
        }
        else {
          param_1 = (vorbis_look_psy *)(1.0 - fVar5 * 0.005 * fVar2);
          if ((float)param_1 < 0.0) {
            local_48[-3] = local_48[-3] * 0.0001;
            goto LAB_005a58da;
          }
        }
        local_48[-3] = local_48[-3] * (float)param_1;
      }
LAB_005a58da:
      fVar3 = *(float *)((int)pfVar8 + -(int)param_3 + (int)pvVar6->noiseoffset[param_4]) +
              *(float *)(((int)param_2 - (int)param_3) + (int)pfVar8);
      if (pvVar6->vi->noisemaxsupp < fVar3) {
        fVar3 = pvVar6->vi->noisemaxsupp;
      }
      fVar5 = *pfVar8 + fVar1;
      if (*pfVar8 + fVar1 < fVar3) {
        fVar5 = fVar3;
      }
      *(float *)(((int)param_5 - (int)param_3) + (int)pfVar8) = fVar5;
      if (param_4 == 1) {
        fVar3 = fVar3 - *(float *)(((int)param_7 - (int)param_3) + (int)pfVar8);
        fVar5 = fVar3 - -17.2;
        if (fVar3 <= -17.2) {
          param_1 = (vorbis_look_psy *)(1.0 - fVar5 * 0.0003 * fVar2);
        }
        else {
          param_1 = (vorbis_look_psy *)(1.0 - fVar5 * 0.005 * fVar2);
          if ((float)param_1 < 0.0) {
            *(float *)(iVar9 + (int)pfVar8) = *(float *)(iVar9 + (int)pfVar8) * 0.0001;
            goto LAB_005a59a9;
          }
        }
        *(float *)(iVar9 + (int)pfVar8) = (float)param_1 * *(float *)(iVar9 + (int)pfVar8);
      }
LAB_005a59a9:
      fVar3 = *(float *)((int)pvVar6->noiseoffset[param_4] + (4 - (int)param_3) + (int)pfVar8) +
              *(float *)(((int)param_2 - (int)param_5) + (int)local_4c);
      if (pvVar6->vi->noisemaxsupp < fVar3) {
        fVar3 = pvVar6->vi->noisemaxsupp;
      }
      fVar5 = pfVar8[1] + fVar1;
      if (pfVar8[1] + fVar1 < fVar3) {
        fVar5 = fVar3;
      }
      *local_4c = fVar5;
      if (param_4 == 1) {
        fVar3 = fVar3 - *(float *)(((int)param_7 - (int)param_5) + (int)local_4c);
        fVar5 = fVar3 - -17.2;
        if (fVar3 <= -17.2) {
          param_1 = (vorbis_look_psy *)(1.0 - fVar5 * 0.0003 * fVar2);
        }
        else {
          param_1 = (vorbis_look_psy *)(1.0 - fVar5 * 0.005 * fVar2);
          if ((float)param_1 < 0.0) {
            *(float *)(iVar10 + (int)local_4c) = *(float *)(iVar10 + (int)local_4c) * 0.0001;
            goto LAB_005a5a78;
          }
        }
        *(float *)(iVar10 + (int)local_4c) = (float)param_1 * *(float *)(iVar10 + (int)local_4c);
      }
LAB_005a5a78:
      pfVar7 = (float *)(((int)param_7 - (int)param_6) + (int)local_48);
      fVar3 = *(float *)((int)pvVar6->noiseoffset[param_4] + (8 - (int)param_3) + (int)pfVar8) +
              *(float *)(((int)param_2 - (int)param_7) + (int)pfVar7);
      if (pvVar6->vi->noisemaxsupp < fVar3) {
        fVar3 = pvVar6->vi->noisemaxsupp;
      }
      fVar5 = pfVar8[2] + fVar1;
      if (pfVar8[2] + fVar1 < fVar3) {
        fVar5 = fVar3;
      }
      local_4c[1] = fVar5;
      if (param_4 == 1) {
        fVar3 = fVar3 - *pfVar7;
        fVar5 = fVar3 - -17.2;
        if (fVar3 <= -17.2) {
          param_1 = (vorbis_look_psy *)(1.0 - fVar5 * 0.0003 * fVar2);
        }
        else {
          param_1 = (vorbis_look_psy *)(1.0 - fVar5 * 0.005 * fVar2);
          if ((float)param_1 < 0.0) {
            *local_48 = *local_48 * 0.0001;
            goto LAB_005a5b56;
          }
        }
        *local_48 = *local_48 * (float)param_1;
      }
LAB_005a5b56:
      local_40 = local_40 + 4;
      local_4c = local_4c + 4;
      local_48 = local_48 + 4;
      pfVar8 = pfVar8 + 4;
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
  }
  if (local_3c < iVar4) {
    pfVar8 = param_3 + local_3c;
    iVar9 = (int)param_6 - (int)param_3;
    do {
      fVar3 = pvVar6->noiseoffset[param_4][local_3c] +
              *(float *)((int)pfVar8 + ((int)param_2 - (int)param_3));
      if (pvVar6->vi->noisemaxsupp < fVar3) {
        fVar3 = pvVar6->vi->noisemaxsupp;
      }
      fVar5 = *pfVar8 + fVar1;
      if (*pfVar8 + fVar1 < fVar3) {
        fVar5 = fVar3;
      }
      *(float *)(((int)param_5 - (int)param_3) + (int)pfVar8) = fVar5;
      if (param_4 == 1) {
        fVar3 = fVar3 - *(float *)(((int)param_7 - (int)param_3) + (int)pfVar8);
        fVar5 = fVar3 - -17.2;
        if (fVar3 <= -17.2) {
          param_1 = (vorbis_look_psy *)(1.0 - fVar5 * 0.0003 * fVar2);
        }
        else {
          param_1 = (vorbis_look_psy *)(1.0 - fVar5 * 0.005 * fVar2);
          if ((float)param_1 < 0.0) {
            *(float *)(iVar9 + (int)pfVar8) = *(float *)(iVar9 + (int)pfVar8) * 0.0001;
            goto LAB_005a5c64;
          }
        }
        *(float *)(iVar9 + (int)pfVar8) = (float)param_1 * *(float *)(iVar9 + (int)pfVar8);
      }
LAB_005a5c64:
      local_3c = local_3c + 1;
      pfVar8 = pfVar8 + 1;
    } while (local_3c < iVar4);
  }
  return;
}

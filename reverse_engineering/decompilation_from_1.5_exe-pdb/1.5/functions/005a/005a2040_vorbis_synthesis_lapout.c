/*
 * Entry: 005a2040
 * Name: vorbis_synthesis_lapout
 * Namespace: Global
 * Signature: int vorbis_synthesis_lapout(vorbis_dsp_state * param_1, float * * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl vorbis_synthesis_lapout(vorbis_dsp_state *param_1,float ***param_2)

{
  float fVar1;
  vorbis_info *pvVar2;
  int *piVar3;
  int iVar4;
  float *pfVar5;
  float *pfVar6;
  uint uVar7;
  float *pfVar8;
  byte bVar9;
  int iVar10;
  float *pfVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  uint uVar15;
  int local_1c;
  
  pvVar2 = param_1->vi;
  piVar3 = pvVar2->codec_setup;
  iVar4 = piVar3[param_1->W];
  bVar9 = (char)piVar3[0x392] + 1;
  uVar15 = *piVar3 >> (bVar9 & 0x1f);
  iVar12 = piVar3[1] >> (bVar9 & 0x1f);
  if (param_1->pcm_returned < 0) {
    return 0;
  }
  if (param_1->centerW == iVar12) {
    local_1c = 0;
    if (0 < pvVar2->channels) {
      do {
        pfVar5 = param_1->pcm[local_1c];
        iVar10 = 0;
        if (3 < iVar12) {
          iVar13 = (iVar12 - 4U >> 2) + 1;
          iVar10 = iVar13 * 4;
          pfVar6 = pfVar5 + iVar12;
          pfVar8 = pfVar5 + 2;
          do {
            fVar1 = pfVar8[-2];
            iVar13 = iVar13 + -1;
            pfVar8[-2] = *pfVar6;
            *pfVar6 = fVar1;
            fVar1 = pfVar8[-1];
            pfVar8[-1] = pfVar6[1];
            pfVar6[1] = fVar1;
            fVar1 = *pfVar8;
            *pfVar8 = pfVar6[2];
            pfVar6[2] = fVar1;
            fVar1 = pfVar8[1];
            pfVar8[1] = pfVar6[3];
            pfVar6[3] = fVar1;
            pfVar6 = pfVar6 + 4;
            pfVar8 = pfVar8 + 4;
          } while (iVar13 != 0);
        }
        if (iVar10 < iVar12) {
          pfVar6 = pfVar5 + iVar10 + iVar12;
          do {
            fVar1 = pfVar5[iVar10];
            iVar13 = iVar10 + 1;
            pfVar5[iVar10] = *pfVar6;
            *pfVar6 = fVar1;
            pfVar6 = pfVar6 + 1;
            iVar10 = iVar13;
          } while (iVar13 < iVar12);
        }
        local_1c = local_1c + 1;
      } while (local_1c < pvVar2->channels);
    }
    param_1->pcm_current = param_1->pcm_current - iVar12;
    param_1->pcm_returned = param_1->pcm_returned - iVar12;
    param_1->centerW = 0;
  }
  if ((param_1->W ^ param_1->lW) == 1) {
    local_1c = 0;
    if (0 < pvVar2->channels) {
      uVar7 = (int)(uVar15 + iVar12) / 2;
      iVar10 = uVar7 - 1;
      do {
        pfVar6 = param_1->pcm[local_1c];
        pfVar5 = pfVar6 + (int)(iVar12 - uVar15) / 2;
        if (-1 < iVar10) {
          iVar13 = iVar10;
          if (3 < (int)uVar7) {
            uVar14 = uVar7 >> 2;
            iVar13 = iVar10 + uVar14 * -4;
            pfVar8 = pfVar5 + (uVar7 - 2);
            pfVar11 = pfVar6 + (uVar7 - 4);
            do {
              pfVar8[1] = pfVar11[3];
              uVar14 = uVar14 - 1;
              *pfVar8 = *(float *)((int)pfVar6 + (0x10 - (int)pfVar5) + (int)(pfVar8 + -4));
              pfVar8[-1] = pfVar11[1];
              pfVar8[-2] = *pfVar11;
              pfVar8 = pfVar8 + -4;
              pfVar11 = pfVar11 + -4;
            } while (uVar14 != 0);
          }
          if (-1 < iVar13) {
            pfVar8 = pfVar5 + iVar13;
            do {
              iVar13 = iVar13 + -1;
              *pfVar8 = *(float *)((int)pfVar8 + ((int)pfVar6 - (int)pfVar5));
              pfVar8 = pfVar8 + -1;
            } while (-1 < iVar13);
          }
        }
        local_1c = local_1c + 1;
      } while (local_1c < pvVar2->channels);
    }
    iVar10 = (int)(iVar12 - uVar15) / 2;
    param_1->pcm_returned = param_1->pcm_returned + iVar10;
  }
  else {
    if (param_1->lW != 0) goto LAB_005a233b;
    local_1c = 0;
    if (0 < pvVar2->channels) {
      do {
        pfVar6 = param_1->pcm[local_1c];
        pfVar5 = pfVar6 + (iVar12 - uVar15);
        iVar10 = uVar15 - 1;
        if (-1 < iVar10) {
          if (3 < (int)uVar15) {
            uVar7 = uVar15 >> 2;
            iVar10 = iVar10 + uVar7 * -4;
            pfVar8 = pfVar5 + (uVar15 - 2);
            pfVar11 = pfVar6 + (uVar15 - 4);
            do {
              pfVar8[1] = pfVar11[3];
              uVar7 = uVar7 - 1;
              *pfVar8 = *(float *)((int)pfVar6 + (0x10 - (int)pfVar5) + (int)(pfVar8 + -4));
              pfVar8[-1] = pfVar11[1];
              pfVar8[-2] = *pfVar11;
              pfVar8 = pfVar8 + -4;
              pfVar11 = pfVar11 + -4;
            } while (uVar7 != 0);
          }
          if (-1 < iVar10) {
            pfVar8 = pfVar5 + iVar10;
            do {
              iVar10 = iVar10 + -1;
              *pfVar8 = *(float *)((int)pfVar8 + ((int)pfVar6 - (int)pfVar5));
              pfVar8 = pfVar8 + -1;
            } while (-1 < iVar10);
          }
        }
        local_1c = local_1c + 1;
      } while (local_1c < pvVar2->channels);
    }
    param_1->pcm_returned = param_1->pcm_returned + (iVar12 - uVar15);
    iVar10 = iVar12 - uVar15;
  }
  param_1->pcm_current = param_1->pcm_current + iVar10;
LAB_005a233b:
  if (param_2 != (float ***)0x0) {
    iVar10 = 0;
    if (0 < pvVar2->channels) {
      do {
        param_1->pcmret[iVar10] = param_1->pcm[iVar10] + param_1->pcm_returned;
        iVar10 = iVar10 + 1;
      } while (iVar10 < pvVar2->channels);
    }
    *param_2 = param_1->pcmret;
  }
  return (iVar12 - param_1->pcm_returned) + (iVar4 >> (bVar9 & 0x1f));
}

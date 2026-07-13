/*
 * Entry: 005a53e0
 * Name: _vp_noisemask
 * Namespace: Global
 * Signature: void _vp_noisemask(vorbis_look_psy * param_1, float * param_2, float * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

void __cdecl _vp_noisemask(vorbis_look_psy *param_1,float *param_2,float *param_3)

{
  float fVar1;
  int iVar2;
  long *plVar3;
  vorbis_info_psy *pvVar4;
  int iVar5;
  float *pfVar6;
  float *pfVar7;
  int extraout_EAX;
  int iVar8;
  undefined4 in_ECX;
  float *pfVar9;
  int iVar10;
  int aiStack_40 [3];
  float afStack_34 [3];
  int iStack_28;
  int local_10;
  
  iVar2 = param_1->n;
  iStack_28 = 0x5a53fd;
  iVar5 = iVar2 * -4;
  (&iStack_28)[-iVar2] = 0xffffffff;
  afStack_34[2 - iVar2] = (float)in_ECX;
  afStack_34[2 - iVar2] = 140.0;
  plVar3 = param_1->bark;
  afStack_34[1 - iVar2] = (float)param_3;
  afStack_34[-iVar2] = (float)param_2;
  aiStack_40[2 - iVar2] = (int)plVar3;
  aiStack_40[1 - iVar2] = iVar2;
  aiStack_40[-iVar2] = 0x5a5421;
  bark_noise_hybridmp(aiStack_40[1 - iVar2],(long *)aiStack_40[2 - iVar2],
                      (float *)afStack_34[-iVar2],(float *)afStack_34[1 - iVar2],
                      afStack_34[2 - iVar2],(&iStack_28)[-iVar2]);
  iVar10 = 0;
  if (3 < iVar2) {
    pfVar7 = param_3 + 1;
    pfVar9 = (float *)(&stack0xffffffe4 + iVar5);
    iVar8 = iVar10;
    do {
      iVar10 = iVar8 + 4;
      pfVar6 = pfVar7 + 4;
      pfVar9[-2] = param_2[iVar8] - pfVar7[-1];
      *(float *)((int)afStack_34 + (iVar5 - (int)param_3) + (int)pfVar6) =
           *(float *)((int)param_2 + (-0x10 - (int)param_3) + (int)pfVar6) - *pfVar7;
      *pfVar9 = *(float *)((int)param_2 + (-0x10 - (int)(&stack0xffffffdc + iVar5)) +
                          (int)(pfVar9 + 4)) - pfVar7[1];
      pfVar9[1] = param_2[iVar8 + 3] - pfVar7[2];
      pfVar7 = pfVar6;
      pfVar9 = pfVar9 + 4;
      iVar8 = iVar10;
    } while (iVar10 < iVar2 + -3);
  }
  if (iVar10 < iVar2) {
    pfVar7 = param_3 + iVar10;
    iVar10 = iVar2 - iVar10;
    do {
      pfVar9 = (float *)(((int)param_2 - (int)param_3) + (int)pfVar7);
      fVar1 = *pfVar7;
      pfVar7 = pfVar7 + 1;
      iVar10 = iVar10 + -1;
      *(float *)((int)&iStack_28 + (iVar5 - (int)param_3) + (int)pfVar7) = *pfVar9 - fVar1;
    } while (iVar10 != 0);
  }
  pvVar4 = param_1->vi;
  (&iStack_28)[-iVar2] = pvVar4->noisewindowfixed;
  plVar3 = param_1->bark;
  afStack_34[2 - iVar2] = (float)pvVar4;
  afStack_34[2 - iVar2] = 0.0;
  afStack_34[1 - iVar2] = (float)param_3;
  afStack_34[-iVar2] = (float)(&stack0xffffffdc + iVar5);
  aiStack_40[2 - iVar2] = (int)plVar3;
  aiStack_40[1 - iVar2] = iVar2;
  aiStack_40[-iVar2] = 0x5a54e5;
  bark_noise_hybridmp(aiStack_40[1 - iVar2],(long *)aiStack_40[2 - iVar2],
                      (float *)afStack_34[-iVar2],(float *)afStack_34[1 - iVar2],
                      afStack_34[2 - iVar2],(&iStack_28)[-iVar2]);
  local_10 = 0;
  if (3 < iVar2) {
    iVar10 = (iVar2 - 4U >> 2) + 1;
    local_10 = iVar10 * 4;
    pfVar7 = (float *)(&stack0xffffffe0 + iVar5);
    pfVar9 = param_2 + 3;
    do {
      iVar10 = iVar10 + -1;
      pfVar7[-1] = pfVar9[-3] - pfVar7[-1];
      *pfVar7 = *(float *)((int)param_2 + (-0x10 - (int)(&stack0xffffffdc + iVar5)) +
                          (int)(pfVar7 + 4)) - *pfVar7;
      pfVar7[1] = pfVar9[-1] - pfVar7[1];
      pfVar7[2] = *pfVar9 - pfVar7[2];
      pfVar7 = pfVar7 + 4;
      pfVar9 = pfVar9 + 4;
    } while (iVar10 != 0);
  }
  if (local_10 < iVar2) {
    iVar10 = iVar2 - local_10;
    pfVar7 = (float *)(&stack0xffffffdc + local_10 * 4 + iVar5);
    do {
      iVar10 = iVar10 + -1;
      *pfVar7 = *(float *)(((int)param_2 - (int)(&stack0xffffffdc + iVar5)) + (int)pfVar7) - *pfVar7
      ;
      pfVar7 = pfVar7 + 1;
    } while (iVar10 != 0);
  }
  if (0 < iVar2) {
    pfVar7 = param_3;
    iVar10 = iVar2;
    do {
      (&iStack_28)[-iVar2] = 0x5a5588;
      _ftol2_sse();
      if (extraout_EAX < 0x28) {
        iVar8 = extraout_EAX;
        if (extraout_EAX < 0) {
          iVar8 = 0;
        }
      }
      else {
        iVar8 = 0x27;
      }
      iVar10 = iVar10 + -1;
      *pfVar7 = param_1->vi->noisecompand[iVar8] +
                *(float *)((int)&iStack_28 + (iVar5 - (int)param_3) + (int)(pfVar7 + 1));
      pfVar7 = pfVar7 + 1;
    } while (iVar10 != 0);
  }
  return;
}

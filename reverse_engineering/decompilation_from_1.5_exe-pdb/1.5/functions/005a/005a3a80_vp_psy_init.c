/*
 * Entry: 005a3a80
 * Name: _vp_psy_init
 * Namespace: Global
 * Signature: void _vp_psy_init(vorbis_look_psy * param_1, vorbis_info_psy * param_2, vorbis_info_psy_global * param_3, int param_4, long param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
_vp_psy_init(vorbis_look_psy *param_1,vorbis_info_psy *param_2,vorbis_info_psy_global *param_3,
            int param_4,long param_5)

{
  size_t _Size;
  float fVar1;
  float fVar2;
  long extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  float *pfVar3;
  long *plVar4;
  int extraout_EAX_02;
  long extraout_EAX_03;
  float ***pppfVar5;
  float **ppfVar6;
  void *pvVar7;
  int extraout_EAX_04;
  int iVar8;
  int iVar9;
  float unaff_EDI;
  int iVar10;
  int iVar11;
  float10 fVar12;
  float10 fVar13;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  int iStack_88;
  int local_84;
  int local_80;
  int iStack_78;
  int iStack_70;
  int iStack_68;
  
  local_84 = -99;
  local_80 = 1;
  memset(param_1,0,0x34);
  param_1->eighth_octave_lines = param_3->eighth_octave_lines;
  fVar12 = (float10)__CIlog();
  fVar13 = (float10)__CIlog();
  floor((double)((float10)(double)fVar12 / fVar13 + (float10)0.5));
  _ftol2_sse();
  param_1->shiftoc = extraout_EAX;
  __CIlog();
  _ftol2_sse();
  param_1->firstoc = extraout_EAX_00;
  __CIlog();
  _ftol2_sse();
  _Size = param_4 * 4;
  param_1->total_octave_lines = (extraout_EAX_01 - extraout_EAX_00) + 1;
  pfVar3 = malloc(_Size);
  param_1->ath = pfVar3;
  plVar4 = malloc(_Size);
  param_1->octave = plVar4;
  plVar4 = malloc(_Size);
  param_1->bark = plVar4;
  param_1->m_val = 1.0;
  param_1->vi = param_2;
  param_1->n = param_4;
  param_1->rate = param_5;
  if (param_5 < 26000) {
    fVar1 = 0.0;
  }
  else if (param_5 < 38000) {
    fVar1 = 0.94;
  }
  else {
    if (param_5 < 0xb3b1) goto LAB_005a3bfe;
    fVar1 = 1.275;
  }
  param_1->m_val = fVar1;
LAB_005a3bfe:
  iVar10 = 0;
  iStack_88 = 0;
  do {
    iVar9 = iStack_88 + 1;
    fVar12 = (float10)__CIexp();
    floor((double)(((fVar12 + fVar12) * (float10)param_4) / (float10)param_5 + (float10)0.5));
    _ftol2_sse();
    fVar1 = ATH[iStack_88];
    if (iVar10 < extraout_EAX_02) {
      fVar2 = (ATH[iStack_88 + 1] - fVar1) / (float)(extraout_EAX_02 - iVar10);
      if (3 < extraout_EAX_02 - iVar10) {
        iVar8 = iVar10 + 2;
        do {
          if (param_4 <= iVar10) goto LAB_005a3d6c;
          param_1->ath[iVar10] = fVar1 + 100.0;
          if (param_4 <= iVar8 + -1) {
            iVar10 = iVar10 + 1;
            goto LAB_005a3d6c;
          }
          param_1->ath[iVar10 + 1] = fVar2 + fVar1 + 100.0;
          fVar1 = fVar2 + fVar1 + fVar2;
          if (param_4 <= iVar8) {
            iVar10 = iVar10 + 2;
            goto LAB_005a3d6c;
          }
          param_1->ath[iVar10 + 2] = fVar1 + 100.0;
          fVar1 = fVar1 + fVar2;
          if (param_4 <= iVar8 + 1) {
            iVar10 = iVar10 + 3;
            goto LAB_005a3d6c;
          }
          iVar11 = iVar10 + 4;
          iVar8 = iVar8 + 4;
          param_1->ath[iVar10 + 3] = fVar1 + 100.0;
          fVar1 = fVar1 + fVar2;
          iVar10 = iVar11;
        } while (iVar11 < extraout_EAX_02 + -3);
      }
      for (; (iVar10 < extraout_EAX_02 && (iVar10 < param_4)); iVar10 = iVar10 + 1) {
        param_1->ath[iVar10] = fVar1 + 100.0;
        fVar1 = fVar1 + fVar2;
      }
    }
LAB_005a3d6c:
    iStack_88 = iVar9;
  } while (iVar9 < 0x57);
  if (iVar10 < param_4) {
    if (3 < param_4 - iVar10) {
      iVar9 = iVar10;
      do {
        param_1->ath[iVar9] = param_1->ath[iVar9 + -1];
        param_1->ath[iVar9 + 1] = param_1->ath[iVar9];
        iVar10 = iVar9 + 4;
        param_1->ath[iVar9 + 2] = param_1->ath[iVar9 + 1];
        param_1->ath[iVar9 + 3] = param_1->ath[iVar9 + 2];
        iVar9 = iVar10;
      } while (iVar10 < param_4 + -3);
    }
    for (; iVar10 < param_4; iVar10 = iVar10 + 1) {
      param_1->ath[iVar10] = param_1->ath[iVar10 + -1];
    }
  }
  iStack_88 = 0;
  if (0 < param_4) {
    iVar10 = param_5 / (param_4 * 2);
    iStack_70 = 0;
    do {
      fVar12 = (float10)__CIatan();
      fVar13 = (float10)__CIatan();
      iStack_68 = param_2->noisewindowlomin + local_84;
      fVar1 = (float)((float10)iStack_70 * (float10)9.999999747378752e-05 +
                     fVar13 * (float10)13.100000381469727 +
                     (float10)(double)(fVar12 * (float10)2.240000009536743));
      if (iStack_68 < iStack_88) {
        fVar2 = param_2->noisewindowlo;
        iStack_78 = iVar10 * local_84;
        do {
          fVar12 = (float10)__CIatan();
          fVar13 = (float10)__CIatan();
          if ((float10)(fVar1 - fVar2) <=
              (float10)iStack_78 * (float10)9.999999747378752e-05 +
              fVar13 * (float10)13.100000381469727 +
              (float10)(double)(fVar12 * (float10)2.240000009536743)) break;
          local_84 = local_84 + 1;
          iStack_78 = iStack_78 + iVar10;
          iStack_68 = iStack_68 + 1;
        } while (iStack_68 < iStack_88);
      }
      if (local_80 <= param_4) {
        iVar9 = param_2->noisewindowhimin;
        iStack_78 = iVar10 * local_80;
        do {
          if (iVar9 + iStack_88 <= local_80) {
            fVar12 = (float10)__CIatan();
            fVar13 = (float10)__CIatan();
            if ((float10)param_2->noisewindowhi + (float10)fVar1 <=
                (float10)iStack_78 * (float10)9.999999747378752e-05 +
                fVar13 * (float10)13.100000381469727 +
                (float10)(double)(fVar12 * (float10)2.240000009536743)) break;
          }
          iStack_78 = iStack_78 + iVar10;
          local_80 = local_80 + 1;
        } while (local_80 <= param_4);
      }
      iStack_70 = iStack_70 + iVar10;
      param_1->bark[iStack_88] = local_84 * 0x10000 + -0x10001 + local_80;
      iStack_88 = iStack_88 + 1;
    } while (iStack_88 < param_4);
  }
  fVar12 = (float10)0.5;
  iVar10 = 0;
  if (0 < param_4) {
    do {
      __CIlog();
      _ftol2_sse();
      param_1->octave[iVar10] = extraout_EAX_03;
      iVar10 = iVar10 + 1;
      fVar12 = extraout_ST0;
    } while (iVar10 < param_4);
  }
  pppfVar5 = setup_tone_curves((float *)(float)((fVar12 * (float10)param_5) / (float10)param_4),
                               (float)param_4,(int)param_2->tone_centerboost,param_2->tone_decay,
                               unaff_EDI);
  param_1->tonecurves = pppfVar5;
  ppfVar6 = malloc(0xc);
  param_1->noiseoffset = ppfVar6;
  iVar10 = 0;
  do {
    pvVar7 = malloc(param_4 * 4);
    *(void **)(iVar10 + (int)param_1->noiseoffset) = pvVar7;
    iVar10 = iVar10 + 4;
  } while (iVar10 < 0xc);
  iVar10 = 0;
  if (0 < param_4) {
    do {
      __CIlog();
      _ftol2_sse();
      iVar9 = iVar10 + 1;
      fVar1 = (float)(extraout_ST0_00 - (float10)extraout_EAX_04);
      fVar2 = 1.0 - fVar1;
      (*param_1->noiseoffset)[iVar10] =
           param_1->vi->noiseoff[0][extraout_EAX_04] * fVar2 +
           param_1->vi->noiseoff[0][extraout_EAX_04 + 1] * fVar1;
      param_1->noiseoffset[1][iVar10] =
           param_1->vi->noiseoff[1][extraout_EAX_04] * fVar2 +
           param_1->vi->noiseoff[1][extraout_EAX_04 + 1] * fVar1;
      param_1->noiseoffset[2][iVar10] =
           fVar2 * param_1->vi->noisecompand[extraout_EAX_04 + -0x11] +
           param_1->vi->noisecompand[extraout_EAX_04 + -0x10] * fVar1;
      iVar10 = iVar9;
    } while (iVar9 < param_4);
  }
  return;
}

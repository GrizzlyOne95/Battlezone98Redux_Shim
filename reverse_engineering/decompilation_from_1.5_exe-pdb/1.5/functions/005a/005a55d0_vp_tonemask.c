/*
 * Entry: 005a55d0
 * Name: _vp_tonemask
 * Namespace: Global
 * Signature: void _vp_tonemask(vorbis_look_psy * param_1, float * param_2, float * param_3, float param_4, float param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */
/* WARNING: Type propagation algorithm not settling */

void __cdecl
_vp_tonemask(vorbis_look_psy *param_1,float *param_2,float *param_3,float param_4,float param_5)

{
  float fVar1;
  int iVar2;
  int iVar3;
  float ***pppfVar4;
  int iVar5;
  vorbis_look_psy *pvVar6;
  int iVar7;
  float *pfVar8;
  int iVar9;
  int iVar10;
  undefined4 auStack_3c [6];
  float fStack_24;
  float fStack_20;
  
  pvVar6 = param_1;
  iVar2 = param_1->total_octave_lines;
  iVar3 = param_1->n;
  fStack_20 = 8.296023e-39;
  iVar5 = iVar2 * -4;
  fVar1 = param_1->vi->ath_adjatt + param_5;
  iVar7 = 0;
  if (0 < iVar2) {
    do {
      *(undefined4 *)(&stack0xffffffe4 + iVar7 * 4 + iVar5) = 0xc61c3c00;
      iVar7 = iVar7 + 1;
    } while (iVar7 < param_1->total_octave_lines);
  }
  if (fVar1 < param_1->vi->ath_maxatt) {
    fVar1 = param_1->vi->ath_maxatt;
  }
  iVar7 = 0;
  if (3 < iVar3) {
    iVar9 = (iVar3 - 4U >> 2) + 1;
    param_1 = (vorbis_look_psy *)0x8;
    iVar7 = iVar9 * 4;
    pfVar8 = param_3 + 2;
    do {
      iVar10 = (-8 - (int)param_3) + (int)pfVar8;
      pfVar8[-2] = *(float *)(iVar10 + (int)pvVar6->ath) + fVar1;
      pfVar8[-1] = *(float *)(iVar10 + 4 + (int)pvVar6->ath) + fVar1;
      iVar9 = iVar9 + -1;
      *pfVar8 = *(float *)((int)&param_1->n + (int)pvVar6->ath) + fVar1;
      pfVar8[1] = *(float *)((4 - (int)param_3) + (int)pfVar8 + (int)pvVar6->ath) + fVar1;
      pfVar8 = pfVar8 + 4;
      param_1 = (vorbis_look_psy *)&param_1->ath;
    } while (iVar9 != 0);
  }
  for (; iVar7 < iVar3; iVar7 = iVar7 + 1) {
    param_3[iVar7] = pvVar6->ath[iVar7] + fVar1;
  }
  *(undefined1 **)((int)&fStack_20 + iVar2 * -4) = &stack0xffffffe4 + iVar5;
  *(float *)((int)&fStack_20 + iVar2 * -4) = param_4;
  (&fStack_24)[-iVar2] = (float)(&stack0xffffffe4 + iVar5);
  pppfVar4 = pvVar6->tonecurves;
  auStack_3c[5 - iVar2] = param_3;
  auStack_3c[4 - iVar2] = param_2;
  auStack_3c[3 - iVar2] = pppfVar4;
  auStack_3c[2 - iVar2] = 0x5a56ed;
  seed_loop((vorbis_look_psy *)auStack_3c[3 - iVar2],(float ***)auStack_3c[4 - iVar2],
            (float *)auStack_3c[5 - iVar2],(float *)(&fStack_24)[-iVar2],
            *(float **)((int)&fStack_20 + iVar2 * -4),*(float *)(&stack0xffffffe4 + iVar5));
  auStack_3c[2 - iVar2] = param_3;
  auStack_3c[1 - iVar2] = &stack0xffffffe4 + iVar5;
  auStack_3c[-iVar2] = 0x5a56f7;
  max_seeds((vorbis_look_psy *)auStack_3c[1 - iVar2],(float *)auStack_3c[2 - iVar2],
            (float *)auStack_3c[3 - iVar2]);
  return;
}

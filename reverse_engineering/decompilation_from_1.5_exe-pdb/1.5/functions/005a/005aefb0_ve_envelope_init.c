/*
 * Entry: 005aefb0
 * Name: _ve_envelope_init
 * Namespace: Global
 * Signature: void _ve_envelope_init(envelope_lookup * param_1, vorbis_info * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _ve_envelope_init(envelope_lookup *param_1,vorbis_info *param_2)

{
  float *pfVar1;
  float fVar2;
  void *pvVar3;
  int iVar4;
  float *pfVar5;
  envelope_filter_state *peVar6;
  int *piVar7;
  int iVar8;
  float10 fVar9;
  float *pfStack_1c;
  int iStack_18;
  
  pvVar3 = param_2->codec_setup;
  iVar4 = param_2->channels;
  param_1->winlength = 0x80;
  param_1->searchstep = 0x40;
  param_1->minenergy = *(float *)((int)pvVar3 + 0xb74);
  param_1->ch = iVar4;
  param_1->storage = 0x80;
  param_1->cursor = *(int *)((int)pvVar3 + 4) / 2;
  pfVar5 = calloc(0x80,4);
  param_1->mdct_win = pfVar5;
  mdct_init(&param_1->mdct,0x80);
  iVar8 = 0;
  do {
    fVar9 = (float10)__CIsin();
    param_1->mdct_win[iVar8] = (float)fVar9;
    fVar2 = param_1->mdct_win[iVar8];
    pfVar5 = param_1->mdct_win + iVar8;
    iVar8 = iVar8 + 1;
    *pfVar5 = fVar2 * fVar2;
  } while (iVar8 < 0x80);
  param_1->band[0].end = 4;
  param_1->band[1].begin = 4;
  param_1->band[2].begin = 6;
  param_1->band[2].end = 6;
  param_1->band[0].begin = 2;
  param_1->band[1].end = 5;
  param_1->band[3].begin = 9;
  param_1->band[3].end = 8;
  param_1->band[4].begin = 0xd;
  param_1->band[4].end = 8;
  param_1->band[5].begin = 0x11;
  param_1->band[5].end = 8;
  param_1->band[6].begin = 0x16;
  param_1->band[6].end = 8;
  iStack_18 = 7;
  pfVar5 = &param_1->band[0].total;
  do {
    fVar2 = pfVar5[-2];
    pfStack_1c = malloc((int)fVar2 * 4);
    iVar8 = 0;
    pfVar5[-1] = (float)pfStack_1c;
    if (0 < (int)fVar2) {
      do {
        fVar9 = (float10)__CIsin();
        pfStack_1c[iVar8] = (float)fVar9;
        pfStack_1c = (float *)pfVar5[-1];
        pfVar1 = pfStack_1c + iVar8;
        iVar8 = iVar8 + 1;
        *pfVar5 = *pfVar1 + *pfVar5;
      } while (iVar8 < (int)fVar2);
    }
    iStack_18 = iStack_18 + -1;
    *pfVar5 = 1.0 / *pfVar5;
    pfVar5 = pfVar5 + 4;
  } while (iStack_18 != 0);
  peVar6 = calloc(iVar4 * 7,0x90);
  param_1->filter = peVar6;
  piVar7 = calloc(param_1->storage,4);
  param_1->mark = piVar7;
  return;
}

/*
 * Entry: 005af9e0
 * Name: _ve_envelope_mark
 * Namespace: Global
 * Signature: int _ve_envelope_mark(vorbis_dsp_state * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl _ve_envelope_mark(vorbis_dsp_state *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  iVar1 = *(int *)param_1->backend_state;
  piVar4 = param_1->vi->codec_setup;
  iVar2 = (int)(piVar4[param_1->W] + (piVar4[param_1->W] >> 0x1f & 3U)) >> 2;
  if (param_1->W == 0) {
    iVar3 = (int)(*piVar4 + (*piVar4 >> 0x1f & 3U)) >> 2;
    iVar5 = iVar3;
  }
  else {
    iVar3 = (int)(piVar4[param_1->nW] + (piVar4[param_1->nW] >> 0x1f & 3U)) >> 2;
    iVar5 = (int)(piVar4[param_1->lW] + (piVar4[param_1->lW] >> 0x1f & 3U)) >> 2;
  }
  iVar5 = (param_1->centerW - iVar2) - iVar5;
  iVar3 = param_1->centerW + iVar2 + iVar3;
  if ((iVar5 <= *(int *)(iVar1 + 0xac)) && (*(int *)(iVar1 + 0xac) < iVar3)) {
    return 1;
  }
  iVar3 = iVar3 / *(int *)(iVar1 + 8);
  iVar5 = iVar5 / *(int *)(iVar1 + 8);
  if (iVar5 < iVar3) {
    piVar4 = (int *)(*(int *)(iVar1 + 0xa0) + iVar5 * 4);
    do {
      if (*piVar4 != 0) {
        return 1;
      }
      iVar5 = iVar5 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar5 < iVar3);
  }
  return 0;
}

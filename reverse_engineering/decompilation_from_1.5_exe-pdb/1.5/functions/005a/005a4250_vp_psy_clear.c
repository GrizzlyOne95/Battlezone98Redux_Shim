/*
 * Entry: 005a4250
 * Name: _vp_psy_clear
 * Namespace: Global
 * Signature: void _vp_psy_clear(vorbis_look_psy * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _vp_psy_clear(vorbis_look_psy *param_1)

{
  int iVar1;
  int iVar2;
  
  if (param_1 != (vorbis_look_psy *)0x0) {
    if (param_1->ath != (float *)0x0) {
      free(param_1->ath);
    }
    if (param_1->octave != (long *)0x0) {
      free(param_1->octave);
    }
    if (param_1->bark != (long *)0x0) {
      free(param_1->bark);
    }
    if (param_1->tonecurves != (float ***)0x0) {
      iVar1 = 0;
      do {
        iVar2 = 0;
        do {
          free(*(void **)(*(int *)(iVar1 + (int)param_1->tonecurves) + iVar2));
          iVar2 = iVar2 + 4;
        } while (iVar2 < 0x20);
        free(*(void **)(iVar1 + (int)param_1->tonecurves));
        iVar1 = iVar1 + 4;
      } while (iVar1 < 0x44);
      free(param_1->tonecurves);
    }
    if (param_1->noiseoffset != (float **)0x0) {
      iVar1 = 0;
      do {
        free(*(void **)((int)param_1->noiseoffset + iVar1));
        iVar1 = iVar1 + 4;
      } while (iVar1 < 0xc);
      free(param_1->noiseoffset);
    }
    memset(param_1,0,0x34);
  }
  return;
}

/*
 * Entry: 005a0f70
 * Name: vorbis_analysis_buffer
 * Namespace: Global
 * Signature: float * * vorbis_analysis_buffer(vorbis_dsp_state * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float ** __cdecl vorbis_analysis_buffer(vorbis_dsp_state *param_1,int param_2)

{
  vorbis_info *pvVar1;
  void *pvVar2;
  float *pfVar3;
  int iVar4;
  
  pvVar1 = param_1->vi;
  pvVar2 = param_1->backend_state;
  if (*(void **)((int)pvVar2 + 0x40) != (void *)0x0) {
    free(*(void **)((int)pvVar2 + 0x40));
  }
  *(undefined4 *)((int)pvVar2 + 0x40) = 0;
  if (*(void **)((int)pvVar2 + 0x44) != (void *)0x0) {
    free(*(void **)((int)pvVar2 + 0x44));
  }
  *(undefined4 *)((int)pvVar2 + 0x44) = 0;
  if (*(void **)((int)pvVar2 + 0x48) != (void *)0x0) {
    free(*(void **)((int)pvVar2 + 0x48));
  }
  *(undefined4 *)((int)pvVar2 + 0x48) = 0;
  if (param_1->pcm_storage <= param_1->pcm_current + param_2) {
    iVar4 = 0;
    param_1->pcm_storage = param_1->pcm_current + param_2 * 2;
    if (0 < pvVar1->channels) {
      do {
        pfVar3 = realloc(param_1->pcm[iVar4],param_1->pcm_storage * 4);
        param_1->pcm[iVar4] = pfVar3;
        iVar4 = iVar4 + 1;
      } while (iVar4 < pvVar1->channels);
    }
  }
  iVar4 = 0;
  if (0 < pvVar1->channels) {
    do {
      param_1->pcmret[iVar4] = param_1->pcm[iVar4] + param_1->pcm_current;
      iVar4 = iVar4 + 1;
    } while (iVar4 < pvVar1->channels);
  }
  return param_1->pcmret;
}

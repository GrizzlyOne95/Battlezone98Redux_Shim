/*
 * Entry: 005a1fc0
 * Name: vorbis_synthesis_pcmout
 * Namespace: Global
 * Signature: int vorbis_synthesis_pcmout(vorbis_dsp_state * param_1, float * * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl vorbis_synthesis_pcmout(vorbis_dsp_state *param_1,float ***param_2)

{
  vorbis_info *pvVar1;
  int iVar2;
  
  pvVar1 = param_1->vi;
  if ((-1 < param_1->pcm_returned) && (param_1->pcm_returned < param_1->pcm_current)) {
    if (param_2 != (float ***)0x0) {
      iVar2 = 0;
      if (0 < pvVar1->channels) {
        do {
          param_1->pcmret[iVar2] = param_1->pcm[iVar2] + param_1->pcm_returned;
          iVar2 = iVar2 + 1;
        } while (iVar2 < pvVar1->channels);
      }
      *param_2 = param_1->pcmret;
    }
    return param_1->pcm_current - param_1->pcm_returned;
  }
  return 0;
}

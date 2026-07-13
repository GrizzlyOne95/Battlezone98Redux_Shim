/*
 * Entry: 005a2010
 * Name: vorbis_synthesis_read
 * Namespace: Global
 * Signature: int vorbis_synthesis_read(vorbis_dsp_state * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl vorbis_synthesis_read(vorbis_dsp_state *param_1,int param_2)

{
  if ((param_2 != 0) && (param_1->pcm_current < param_1->pcm_returned + param_2)) {
    return -0x83;
  }
  param_1->pcm_returned = param_1->pcm_returned + param_2;
  return 0;
}

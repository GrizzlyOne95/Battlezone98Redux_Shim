/*
 * Entry: 005a2380
 * Name: vorbis_window
 * Namespace: Global
 * Signature: float * vorbis_window(vorbis_dsp_state * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float * __cdecl vorbis_window(vorbis_dsp_state *param_1,int param_2)

{
  int iVar1;
  float *pfVar2;
  
  iVar1 = *(int *)((int)param_1->backend_state + param_2 * 4 + 4);
  if (iVar1 + -1 < 0) {
    return (float *)0x0;
  }
  pfVar2 = _vorbis_window_get(iVar1 - *(int *)((int)param_1->vi->codec_setup + 0xe48));
  return pfVar2;
}

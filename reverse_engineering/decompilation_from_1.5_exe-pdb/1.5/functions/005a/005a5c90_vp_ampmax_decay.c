/*
 * Entry: 005a5c90
 * Name: _vp_ampmax_decay
 * Namespace: Global
 * Signature: float _vp_ampmax_decay(float param_1, vorbis_dsp_state * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl _vp_ampmax_decay(float param_1,vorbis_dsp_state *param_2)

{
  void *pvVar1;
  float fVar2;
  
  pvVar1 = param_2->vi->codec_setup;
  fVar2 = ((float)(*(int *)((int)pvVar1 + param_2->W * 4) / 2) / (float)param_2->vi->rate) *
          *(float *)((int)pvVar1 + 0xb78) + param_1;
  if (fVar2 < -9999.0) {
    return -9999.0;
  }
  return fVar2;
}

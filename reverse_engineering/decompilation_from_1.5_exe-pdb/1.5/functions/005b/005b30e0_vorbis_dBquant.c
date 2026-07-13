/*
 * Entry: 005b30e0
 * Name: vorbis_dBquant
 * Namespace: Global
 * Signature: int vorbis_dBquant(float * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl vorbis_dBquant(float *param_1)

{
  uint extraout_EAX;
  
  _ftol2_sse();
  if (0x3ff < (int)extraout_EAX) {
    return 0x3ff;
  }
  return extraout_EAX & ((int)extraout_EAX < 0) - 1;
}

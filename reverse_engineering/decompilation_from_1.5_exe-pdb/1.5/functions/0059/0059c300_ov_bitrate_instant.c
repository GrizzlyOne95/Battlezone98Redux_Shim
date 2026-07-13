/*
 * Entry: 0059c300
 * Name: ov_bitrate_instant
 * Namespace: Global
 * Signature: long ov_bitrate_instant(OggVorbis_File * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl ov_bitrate_instant(OggVorbis_File *param_1)

{
  long lVar1;
  long extraout_EAX;
  
  if (param_1->ready_state < 2) {
    lVar1 = -0x83;
  }
  else if (param_1->samptrack == 0.0) {
    lVar1 = -1;
  }
  else {
    _ftol2_sse();
    param_1->bittrack = 0.0;
    param_1->samptrack = 0.0;
    lVar1 = extraout_EAX;
  }
  return lVar1;
}

/*
 * Entry: 0059f180
 * Name: _ov_getlap
 * Namespace: Global
 * Signature: void _ov_getlap(OggVorbis_File * param_1, vorbis_info * param_2, vorbis_dsp_state * param_3, float * * param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
_ov_getlap(OggVorbis_File *param_1,vorbis_info *param_2,vorbis_dsp_state *param_3,float **param_4,
          int param_5)

{
  int iVar1;
  int local_1c;
  int local_14;
  int local_10;
  int local_c;
  float **local_8;
  
  local_c = 0;
  do {
    while( true ) {
      if (param_5 <= local_c) goto LAB_0059f24b;
      local_14 = vorbis_synthesis_pcmout(param_3,&local_8);
      if (local_14 == 0) break;
      if (param_5 - local_c < local_14) {
        local_14 = param_5 - local_c;
      }
      for (local_10 = 0; local_10 < param_2->channels; local_10 = local_10 + 1) {
        memcpy(param_4[local_10] + local_c,local_8[local_10],local_14 << 2);
      }
      local_c = local_c + local_14;
      vorbis_synthesis_read(param_3,local_14);
    }
    iVar1 = _fetch_and_process_packet(param_1,(ogg_packet *)0x0,1,0);
  } while (iVar1 != -2);
LAB_0059f24b:
  if (local_c < param_5) {
    local_1c = vorbis_synthesis_lapout(&param_1->vd,&local_8);
    if (local_1c == 0) {
      for (local_10 = 0; local_10 < param_2->channels; local_10 = local_10 + 1) {
        memset(param_4[local_10] + local_c,0,param_5 * 4 - local_c);
      }
    }
    else {
      if (param_5 - local_c < local_1c) {
        local_1c = param_5 - local_c;
      }
      for (local_10 = 0; local_10 < param_2->channels; local_10 = local_10 + 1) {
        memcpy(param_4[local_10] + local_c,local_8[local_10],local_1c << 2);
      }
    }
  }
  return;
}

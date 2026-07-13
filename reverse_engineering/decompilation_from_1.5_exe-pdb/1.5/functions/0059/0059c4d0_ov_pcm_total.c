/*
 * Entry: 0059c4d0
 * Name: ov_pcm_total
 * Namespace: Global
 * Signature: long64 ov_pcm_total(OggVorbis_File * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long64 __cdecl ov_pcm_total(OggVorbis_File *param_1,int param_2)

{
  longlong lVar1;
  long64 lVar2;
  int local_8;
  
  if (param_1->ready_state < 2) {
    lVar1 = -0x83;
  }
  else if ((param_1->seekable == 0) || (param_1->links <= param_2)) {
    lVar1 = -0x83;
  }
  else if (param_2 < 0) {
    lVar1 = 0;
    for (local_8 = 0; local_8 < param_1->links; local_8 = local_8 + 1) {
      lVar2 = ov_pcm_total(param_1,local_8);
      lVar1 = lVar2 + lVar1;
    }
  }
  else {
    lVar1 = CONCAT44(*(undefined4 *)((int)param_1->pcmlengths + param_2 * 0x10 + 0xc),
                     (int)param_1->pcmlengths[param_2 * 2 + 1]);
  }
  return lVar1;
}

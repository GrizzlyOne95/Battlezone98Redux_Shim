/*
 * Entry: 0059e420
 * Name: ov_pcm_tell
 * Namespace: Global
 * Signature: long64 ov_pcm_tell(OggVorbis_File * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long64 __cdecl ov_pcm_tell(OggVorbis_File *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  if (param_1->ready_state < 2) {
    uVar1 = 0xffffff7d;
    uVar2 = 0xffffffff;
  }
  else {
    uVar1 = (undefined4)param_1->pcm_offset;
    uVar2 = *(undefined4 *)((int)&param_1->pcm_offset + 4);
  }
  return CONCAT44(uVar2,uVar1);
}

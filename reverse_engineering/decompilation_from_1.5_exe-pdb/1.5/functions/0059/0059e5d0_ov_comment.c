/*
 * Entry: 0059e5d0
 * Name: ov_comment
 * Namespace: Global
 * Signature: vorbis_comment * ov_comment(OggVorbis_File * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

vorbis_comment * __cdecl ov_comment(OggVorbis_File *param_1,int param_2)

{
  vorbis_comment *pvVar1;
  
  if (param_1->seekable == 0) {
    pvVar1 = param_1->vc;
  }
  else if (param_2 < 0) {
    if (param_1->ready_state < 3) {
      pvVar1 = param_1->vc;
    }
    else {
      pvVar1 = param_1->vc + param_1->current_link;
    }
  }
  else if (param_2 < param_1->links) {
    pvVar1 = param_1->vc + param_2;
  }
  else {
    pvVar1 = (vorbis_comment *)0x0;
  }
  return pvVar1;
}

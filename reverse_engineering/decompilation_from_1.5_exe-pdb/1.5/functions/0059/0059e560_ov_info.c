/*
 * Entry: 0059e560
 * Name: ov_info
 * Namespace: Global
 * Signature: vorbis_info * ov_info(OggVorbis_File * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

vorbis_info * __cdecl ov_info(OggVorbis_File *param_1,int param_2)

{
  vorbis_info *pvVar1;
  
  if (param_1->seekable == 0) {
    pvVar1 = param_1->vi;
  }
  else if (param_2 < 0) {
    if (param_1->ready_state < 3) {
      pvVar1 = param_1->vi;
    }
    else {
      pvVar1 = param_1->vi + param_1->current_link;
    }
  }
  else if (param_2 < param_1->links) {
    pvVar1 = param_1->vi + param_2;
  }
  else {
    pvVar1 = (vorbis_info *)0x0;
  }
  return pvVar1;
}

/*
 * Entry: 0059dc60
 * Name: _make_decode_ready
 * Namespace: Global
 * Signature: int _make_decode_ready(OggVorbis_File * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl _make_decode_ready(OggVorbis_File *param_1)

{
  int iVar1;
  
  if (param_1->ready_state < 4) {
    if (param_1->ready_state < 3) {
      iVar1 = -0x81;
    }
    else {
      if (param_1->seekable == 0) {
        iVar1 = vorbis_synthesis_init(&param_1->vd,param_1->vi);
        if (iVar1 != 0) {
          return -0x89;
        }
      }
      else {
        iVar1 = vorbis_synthesis_init(&param_1->vd,param_1->vi + param_1->current_link);
        if (iVar1 != 0) {
          return -0x89;
        }
      }
      vorbis_block_init(&param_1->vd,&param_1->vb);
      param_1->ready_state = 4;
      param_1->bittrack = 0.0;
      param_1->samptrack = 0.0;
      iVar1 = 0;
    }
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

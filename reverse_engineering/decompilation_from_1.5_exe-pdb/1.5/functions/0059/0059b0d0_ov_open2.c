/*
 * Entry: 0059b0d0
 * Name: _ov_open2
 * Namespace: Global
 * Signature: int _ov_open2(OggVorbis_File * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl _ov_open2(OggVorbis_File *param_1)

{
  int iVar1;
  
  if (param_1->ready_state == 1) {
    param_1->ready_state = 2;
    if (param_1->seekable == 0) {
      param_1->ready_state = 3;
      iVar1 = 0;
    }
    else {
      iVar1 = _open_seekable2(param_1);
      if (iVar1 != 0) {
        param_1->datasource = (void *)0x0;
        ov_clear(param_1);
      }
    }
  }
  else {
    iVar1 = -0x83;
  }
  return iVar1;
}

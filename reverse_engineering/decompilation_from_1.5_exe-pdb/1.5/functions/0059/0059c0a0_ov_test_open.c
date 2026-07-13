/*
 * Entry: 0059c0a0
 * Name: ov_test_open
 * Namespace: Global
 * Signature: int ov_test_open(OggVorbis_File * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ov_test_open(OggVorbis_File *param_1)

{
  int iVar1;
  
  if (param_1->ready_state == 1) {
    iVar1 = _ov_open2(param_1);
  }
  else {
    iVar1 = -0x83;
  }
  return iVar1;
}

/*
 * Entry: 0059bfd0
 * Name: ov_halfrate_p
 * Namespace: Global
 * Signature: int ov_halfrate_p(OggVorbis_File * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ov_halfrate_p(OggVorbis_File *param_1)

{
  int iVar1;
  
  if (param_1->vi == (vorbis_info *)0x0) {
    iVar1 = -0x83;
  }
  else {
    iVar1 = vorbis_synthesis_halfrate_p(param_1->vi);
  }
  return iVar1;
}

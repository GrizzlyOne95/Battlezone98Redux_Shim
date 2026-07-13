/*
 * Entry: 0059f550
 * Name: ov_pcm_seek_page_lap
 * Namespace: Global
 * Signature: int ov_pcm_seek_page_lap(OggVorbis_File * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ov_pcm_seek_page_lap(OggVorbis_File *param_1,long64 param_2)

{
  int iVar1;
  _func___cdecl_int_OggVorbis_File_ptr_long64 *unaff_EBP;
  
  iVar1 = _ov_64_seek_lap(param_1,CONCAT44(ov_pcm_seek_page,(undefined4)param_2),unaff_EBP);
  return iVar1;
}

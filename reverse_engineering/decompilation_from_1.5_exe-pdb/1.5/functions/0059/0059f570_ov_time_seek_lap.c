/*
 * Entry: 0059f570
 * Name: ov_time_seek_lap
 * Namespace: Global
 * Signature: int ov_time_seek_lap(OggVorbis_File * param_1, double param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ov_time_seek_lap(OggVorbis_File *param_1,double param_2)

{
  int iVar1;
  _func___cdecl_int_OggVorbis_File_ptr_double *unaff_EBP;
  
  iVar1 = _ov_d_seek_lap(param_1,(double)CONCAT44(ov_time_seek,param_2._0_4_),unaff_EBP);
  return iVar1;
}

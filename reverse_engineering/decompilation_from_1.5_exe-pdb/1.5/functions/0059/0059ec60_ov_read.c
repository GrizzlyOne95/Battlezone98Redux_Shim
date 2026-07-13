/*
 * Entry: 0059ec60
 * Name: ov_read
 * Namespace: Global
 * Signature: long ov_read(OggVorbis_File * param_1, char * param_2, int param_3, int param_4, int param_5, int param_6, int * param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl
ov_read(OggVorbis_File *param_1,char *param_2,int param_3,int param_4,int param_5,int param_6,
       int *param_7)

{
  long lVar1;
  
  lVar1 = ov_read_filter(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                         (_func___cdecl_void_float_ptr_ptr_long_long_void_ptr *)0x0,(void *)0x0);
  return lVar1;
}

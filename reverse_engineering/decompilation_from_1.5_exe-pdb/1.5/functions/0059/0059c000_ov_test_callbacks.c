/*
 * Entry: 0059c000
 * Name: ov_test_callbacks
 * Namespace: Global
 * Signature: int ov_test_callbacks(void * param_1, OggVorbis_File * param_2, char * param_3, long param_4, ov_callbacks param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
ov_test_callbacks(void *param_1,OggVorbis_File *param_2,char *param_3,long param_4,
                 ov_callbacks param_5)

{
  int iVar1;
  
  iVar1 = _ov_open1(param_1,param_2,param_3,param_4,param_5);
  return iVar1;
}

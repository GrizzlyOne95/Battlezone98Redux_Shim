/*
 * Entry: 0059bde0
 * Name: ov_open
 * Namespace: Global
 * Signature: int ov_open(_iobuf * param_1, OggVorbis_File * param_2, char * param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ov_open(_iobuf *param_1,OggVorbis_File *param_2,char *param_3,long param_4)

{
  ov_callbacks oVar1;
  int iVar2;
  
  oVar1.seek_func = _fseek64_wrap;
  oVar1.read_func = fread_exref;
  oVar1.close_func = fclose_exref;
  oVar1.tell_func = ftell_exref;
  iVar2 = ov_open_callbacks(param_1,param_2,param_3,param_4,oVar1);
  return iVar2;
}

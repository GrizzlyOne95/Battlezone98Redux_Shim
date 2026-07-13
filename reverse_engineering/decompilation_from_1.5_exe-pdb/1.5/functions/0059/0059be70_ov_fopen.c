/*
 * Entry: 0059be70
 * Name: ov_fopen
 * Namespace: Global
 * Signature: int ov_fopen(char * param_1, OggVorbis_File * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ov_fopen(char *param_1,OggVorbis_File *param_2)

{
  FILE *_File;
  int iVar1;
  
  _File = fopen(param_1,&DAT_0064d4a8);
  if (_File == (FILE *)0x0) {
    iVar1 = -1;
  }
  else {
    iVar1 = ov_open((_iobuf *)_File,param_2,(char *)0x0,0);
    if (iVar1 != 0) {
      fclose(_File);
    }
  }
  return iVar1;
}

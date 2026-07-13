/*
 * Entry: 004fa072
 * Name: Pcx_Read_Palette
 * Namespace: Global
 * Signature: int Pcx_Read_Palette(char * param_1, RGB * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl Pcx_Read_Palette(char *param_1,RGB *param_2)

{
  FILE *_File;
  int iVar1;
  undefined1 local_388 [768];
  char local_88;
  char local_87;
  char local_85;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  _File = fopen(param_1,"rb");
  iVar1 = 0;
  if (_File != (FILE *)0x0) {
    fread(&local_88,0x80,1,_File);
    if (((local_88 == '\n') || (local_87 == '\x05')) || (local_85 == '\b')) {
      fseek(_File,-0x300,2);
      fread(local_388,0x100,3,_File);
      iVar1 = 1;
    }
    else {
      fclose(_File);
      iVar1 = 0;
    }
  }
  return iVar1;
}

/*
 * Entry: 004ba2b9
 * Name: write_temp_to_input
 * Namespace: Global
 * Signature: int write_temp_to_input(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl write_temp_to_input(void)

{
  FILE *_File;
  FILE *_File_00;
  int iVar1;
  char local_104 [256];
  uint local_4;
  
  local_4 = __security_cookie ^ (uint)local_104;
  _chmod("input.map",0x80);
  _File = fopen("input.map","w");
  _File_00 = fopen("temp.map","r");
  iVar1 = getInputMapLine(local_104,0xff,(_iobuf *)_File_00);
  while (iVar1 != 0) {
    fprintf(_File,"%s\n",local_104);
    if (local_104[0] == '}') {
      fprintf(_File,"\n");
    }
    iVar1 = getInputMapLine(local_104,0xff,(_iobuf *)_File_00);
  }
  fclose(_File_00);
  fclose(_File);
  _chmod("input.map",0x100);
  return 1;
}

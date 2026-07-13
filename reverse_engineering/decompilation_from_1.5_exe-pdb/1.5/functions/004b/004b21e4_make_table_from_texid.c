/*
 * Entry: 004b21e4
 * Name: make_table_from_texid
 * Namespace: Global
 * Signature: void make_table_from_texid(char * param_1, textab * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl make_table_from_texid(char *param_1,textab *param_2)

{
  char *_Dest;
  int unaff_ESI;
  
  *(undefined4 *)(unaff_ESI + 0x1c) = 1;
  *(undefined4 *)(unaff_ESI + 0x20) = 1;
  _Dest = operator_new__(0x10);
  *(char **)(unaff_ESI + 0x2c) = _Dest;
  strncpy(_Dest,param_1,0xf);
  *(undefined4 *)(unaff_ESI + 0x10) = 0;
  return;
}

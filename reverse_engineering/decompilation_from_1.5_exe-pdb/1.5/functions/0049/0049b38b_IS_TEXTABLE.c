/*
 * Entry: 0049b38b
 * Name: IS_TEXTABLE
 * Namespace: Global
 * Signature: int IS_TEXTABLE(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IS_TEXTABLE(char *param_1)

{
  char *_Str1;
  int iVar1;
  
  _Str1 = strrchr(param_1,0x2e);
  if (_Str1 != (char *)0x0) {
    iVar1 = _stricmp(_Str1,".map");
    return iVar1;
  }
  return 0;
}

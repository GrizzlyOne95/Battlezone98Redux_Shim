/*
 * Entry: 004fbccf
 * Name: GetSpriteIndex
 * Namespace: Global
 * Signature: int GetSpriteIndex(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetSpriteIndex(char *param_1)

{
  int iVar1;
  char (*_Str1) [32];
  int iVar2;
  
  if (param_1 == (char *)0x0) {
    return 0;
  }
  iVar2 = spriteTableSize + -1;
  if (0 < iVar2) {
    _Str1 = nameTable + iVar2;
    do {
      iVar1 = _strnicmp(*_Str1,param_1,0x20);
      if (iVar1 == 0) {
        return iVar2;
      }
      iVar2 = iVar2 + -1;
      _Str1 = _Str1 + -1;
    } while (0 < iVar2);
  }
  return 0;
}

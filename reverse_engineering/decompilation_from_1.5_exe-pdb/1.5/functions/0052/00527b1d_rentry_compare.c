/*
 * Entry: 00527b1d
 * Name: rentry_compare
 * Namespace: Global
 * Signature: int rentry_compare(char * _Str1, char * _Str2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl rentry_compare(char *_Str1,char *_Str2)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00527b1d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = _stricmp(_Str1,_Str2);
  return iVar1;
}

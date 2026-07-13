/*
 * Entry: 005bafa0
 * Name: l_strcmp
 * Namespace: Global
 * Signature: int l_strcmp(TString * param_1, TString * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl l_strcmp(TString *param_1,TString *param_2)

{
  char cVar1;
  int in_EAX;
  char *pcVar2;
  int iVar3;
  int in_ECX;
  char *_Str2;
  char *_Str1;
  int local_c;
  int local_8;
  
  _Str1 = (char *)(in_ECX + 0x10);
  local_8 = *(int *)(in_ECX + 0xc);
  _Str2 = (char *)(in_EAX + 0x10);
  local_c = *(int *)(in_EAX + 0xc);
  while( true ) {
    iVar3 = strcoll(_Str1,_Str2);
    if (iVar3 != 0) {
      return iVar3;
    }
    pcVar2 = _Str1;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    iVar3 = (int)pcVar2 - (int)(_Str1 + 1);
    if (iVar3 == local_c) break;
    if (iVar3 == local_8) {
      return -1;
    }
    iVar3 = iVar3 + 1;
    local_8 = local_8 - iVar3;
    _Str1 = _Str1 + iVar3;
    _Str2 = _Str2 + iVar3;
    local_c = local_c - iVar3;
  }
  return (uint)(iVar3 != local_8);
}

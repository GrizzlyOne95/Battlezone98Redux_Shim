/*
 * Entry: 0054edb5
 * Name: GetPrjFileInfo
 * Namespace: Global
 * Signature: int GetPrjFileInfo(char * param_1, char * param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl GetPrjFileInfo(char *param_1,char *param_2,long param_3)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *_Str;
  long local_114;
  char *local_110;
  int local_10c;
  char local_108 [108];
  undefined1 local_9c [148];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_9c;
  local_10c = 0;
  local_114 = GetItemSize("PrjInfo.txt");
  if (local_114 == 0) {
    return local_10c;
  }
  local_110 = UseItem("PrjInfo.txt");
  if (local_110 == (char *)0x0) {
    return local_10c;
  }
  iVar2 = sgets(&local_110,local_108,&local_114,0x100);
  while (iVar2 != 0) {
    _Str = local_108;
    cVar1 = local_108[0];
    while ((cVar1 != '\0' && (iVar2 = isspace((int)*_Str), iVar2 != 0))) {
      _Str = _Str + 1;
      cVar1 = *_Str;
    }
    pcVar3 = strchr(_Str,0x3a);
    if ((pcVar3 != (char *)0x0) &&
       (iVar2 = _strnicmp(_Str,param_1,(int)pcVar3 - (int)_Str), iVar2 == 0)) {
      pcVar3 = pcVar3 + 1;
      cVar1 = *pcVar3;
      if (cVar1 != '\0') goto LAB_0054ee9e;
      break;
    }
    iVar2 = sgets(&local_110,local_108,&local_114,0x100);
  }
  goto LAB_0054eed5;
  while( true ) {
    pcVar3 = pcVar3 + 1;
    cVar1 = *pcVar3;
    if (cVar1 == '\0') break;
LAB_0054ee9e:
    iVar2 = isspace((int)cVar1);
    if (iVar2 == 0) break;
  }
  if (*pcVar3 != '\0') {
    strncpy(param_2,pcVar3,param_3);
    local_10c = 1;
  }
LAB_0054eed5:
  UnlockItem("PrjInfo.txt");
  return local_10c;
}

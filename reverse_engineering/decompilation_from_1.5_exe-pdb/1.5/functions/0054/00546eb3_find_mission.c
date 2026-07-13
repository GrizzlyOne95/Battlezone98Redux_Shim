/*
 * Entry: 00546eb3
 * Name: find_mission
 * Namespace: Global
 * Signature: int find_mission(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl find_mission(char *param_1)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  char local_210 [260];
  char local_10c [260];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  iVar3 = -(int)param_1;
  do {
    cVar1 = *param_1;
    param_1[(int)(local_10c + iVar3)] = cVar1;
    param_1 = param_1 + 1;
  } while (cVar1 != '\0');
  pcVar2 = strchr(local_10c,0x2e);
  if (pcVar2 != (char *)0x0) {
    *pcVar2 = '\0';
  }
  sprintf(local_210,"%s.bzn",local_10c);
  iVar3 = zixGetFileSize(local_210);
  return iVar3;
}

/*
 * Entry: 00524eb9
 * Name: GetKeyString
 * Namespace: Global
 * Signature: int GetKeyString(char * param_1, char * param_2, char * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl GetKeyString(char *param_1,char *param_2,char *param_3,int param_4)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  char *in_ECX;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  int iVar8;
  char *pcVar9;
  char *local_110;
  undefined4 local_10c;
  char local_108 [116];
  undefined1 local_94 [140];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_94;
  local_10c = param_2;
  pcVar2 = in_ECX;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  if ((int)pcVar2 - (int)(in_ECX + 1) < 0xff) {
    pcVar6 = param_1 + 1;
    pcVar3 = param_1;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    if ((int)pcVar3 - (int)pcVar6 < 0xff) {
      local_108[0] = '[';
      local_108[1] = '\0';
      pcVar4 = in_ECX;
      do {
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
      pcVar9 = (char *)((int)&local_10c + 3);
      do {
        pcVar7 = pcVar9 + 1;
        pcVar9 = pcVar9 + 1;
      } while (*pcVar7 != '\0');
      pcVar7 = in_ECX;
      for (uVar5 = (uint)((int)pcVar4 - (int)in_ECX) >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
        pcVar7 = pcVar7 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar5 = (int)pcVar4 - (int)in_ECX & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar9 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar9 = pcVar9 + 1;
      }
      pcVar4 = (char *)((int)&local_10c + 3);
      do {
        pcVar9 = pcVar4 + 1;
        pcVar4 = pcVar4 + 1;
      } while (*pcVar9 != '\0');
      *(char (*) [2])pcVar4 = (char  [2])0x5d;
      _strupr(local_108);
      pcVar4 = strstr(pINIBuffer,local_108);
      if ((pcVar4 != (char *)0x0) &&
         (pcVar4 = pcVar4 + ((int)pcVar2 - (int)(in_ECX + 1)) + 2, pcVar4 < pINIBuffer + fileLen)) {
        local_110 = strstr(pcVar4,"[");
        if (local_110 == (char *)0x0) {
          local_110 = pINIBuffer + fileLen;
        }
        iVar8 = -(int)param_1;
        do {
          cVar1 = *param_1;
          param_1[(int)(local_108 + iVar8)] = cVar1;
          param_1 = param_1 + 1;
        } while (cVar1 != '\0');
        _strupr(local_108);
        pcVar2 = strstr(pcVar4,local_108);
        if ((pcVar2 != (char *)0x0) && (pcVar2 < local_110)) {
          pcVar2 = pcVar2 + ((int)pcVar3 - (int)pcVar6) + 1;
          pcVar6 = pINIBuffer + fileLen;
          for (iVar8 = 1;
              ((pcVar2 < pcVar6 && (cVar1 = *pcVar2, cVar1 != '\n')) && (iVar8 < (int)param_3));
              iVar8 = iVar8 + 1) {
            pcVar2 = pcVar2 + 1;
            *local_10c = cVar1;
            local_10c = local_10c + 1;
          }
          *local_10c = '\0';
          return 0;
        }
      }
    }
  }
  return -1;
}

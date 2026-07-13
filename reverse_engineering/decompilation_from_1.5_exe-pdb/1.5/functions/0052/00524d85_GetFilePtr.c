/*
 * Entry: 00524d85
 * Name: GetFilePtr
 * Namespace: Global
 * Signature: char * GetFilePtr(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl GetFilePtr(char *param_1)

{
  byte *pbVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  byte *pbVar5;
  byte *pbVar6;
  char *pcVar7;
  
  if (((pINIBuffer != (char *)0x0) && (fileLen != 0)) &&
     (iVar4 = _stricmp(param_1,lastFileName), iVar4 == 0)) {
    return pINIBuffer;
  }
  lastFileName[0] = '\0';
  fileLen = 0;
  pINIBuffer = (char *)0x0;
  pbVar5 = zixReadFile(param_1,&fileLen);
  if (pbVar5 != (byte *)0x0) {
    pbVar1 = pbVar5 + fileLen;
    pcVar7 = INIBuffer;
    pbVar6 = pbVar5;
    if (pbVar5 < pbVar1) {
      while (pcVar7 < INIBuffer + 0x1fff) {
        bVar2 = *pbVar6;
        if ((bVar2 == 0x3b) || ((bVar2 == 0x2f && (pbVar6[1] == 0x2f)))) {
          while (bVar2 != 10) {
            if (pbVar1 <= pbVar6) goto LAB_00524e49;
            pbVar6 = pbVar6 + 1;
            bVar2 = *pbVar6;
          }
        }
        else {
          if (bVar2 == 0x22) {
            while( true ) {
              pbVar6 = pbVar6 + 1;
              if ((*pbVar6 == 0x22) || (pbVar1 <= pbVar6)) break;
              *pcVar7 = *pbVar6;
              pcVar7 = pcVar7 + 1;
            }
          }
          else if ((0x20 < bVar2) || (bVar2 == 10)) {
            *pcVar7 = bVar2;
            pcVar7 = pcVar7 + 1;
          }
          pbVar6 = pbVar6 + 1;
        }
        if (pbVar1 <= pbVar6) break;
      }
    }
LAB_00524e49:
    *pcVar7 = 0;
    INIBuffer[0x1fff] = '\0';
    pINIBuffer = INIBuffer;
    _strupr(INIBuffer);
    pcVar7 = pINIBuffer;
    do {
      cVar3 = *pcVar7;
      pcVar7 = pcVar7 + 1;
    } while (cVar3 != '\0');
    fileLen = (int)pcVar7 - (int)(pINIBuffer + 1);
    strncpy(lastFileName,param_1,0x100);
    zixFree(pbVar5);
    if ((0 < fileLen) && (pINIBuffer != (char *)0x0)) {
      return pINIBuffer;
    }
    fileLen = 0;
    pINIBuffer = (char *)0x0;
  }
  return (char *)0x0;
}

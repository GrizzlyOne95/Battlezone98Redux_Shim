/*
 * Entry: 00525726
 * Name: PrjID2Filename
 * Namespace: Global
 * Signature: char * PrjID2Filename(long64 param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl PrjID2Filename(long64 param_1,char *param_2)

{
  char *pcVar1;
  char cVar2;
  uint uVar3;
  byte bVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  bool bVar8;
  
  uVar3 = 0;
  do {
    bVar4 = *(byte *)((int)&param_1 + uVar3) & 0x7f;
    if (bVar4 == 0) break;
    filename[uVar3] = bVar4;
    uVar3 = uVar3 + 1;
  } while (uVar3 < 8);
  if (uVar3 != 0) {
    iVar5 = 5;
    pcVar1 = filename + uVar3;
    bVar8 = true;
    *pcVar1 = '\0';
    pcVar6 = filename;
    pcVar7 = "null";
    do {
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      bVar8 = *pcVar6 == *pcVar7;
      pcVar6 = pcVar6 + 1;
      pcVar7 = pcVar7 + 1;
    } while (bVar8);
    if (!bVar8) {
      if (param_2 == (char *)0x0) {
        if (uVar3 < 8) {
          memset(pcVar1,0,8 - uVar3);
        }
      }
      else {
        iVar5 = (int)pcVar1 - (int)param_2;
        do {
          cVar2 = *param_2;
          param_2[iVar5] = cVar2;
          param_2 = param_2 + 1;
        } while (cVar2 != '\0');
      }
      return filename;
    }
  }
  return (char *)0x0;
}

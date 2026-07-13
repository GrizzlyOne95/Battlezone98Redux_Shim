/*
 * Entry: 004839f7
 * Name: MakeRDName
 * Namespace: Global
 * Signature: char * MakeRDName(char * param_1, char * param_2, long param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl MakeRDName(char *param_1,char *param_2,long param_3,long param_4)

{
  char *pcVar1;
  char cVar2;
  char cVar3;
  char *pcVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  
  cVar2 = *(char *)((int)SampleMods + (UserProfilePtr->graphicDetail).resolution + 0x27);
  if (param_1 == (char *)0x0) {
    pcVar4 = (char *)0x0;
  }
  else {
    if (param_3 == 0) {
      strncpy(resName,param_1,param_4);
      resName[param_4] = cVar2;
      pcVar4 = param_1 + param_4;
      iVar6 = (param_4 + 1) - (int)pcVar4;
      do {
        cVar2 = *pcVar4;
        pcVar4[(int)(resName + iVar6)] = cVar2;
        pcVar4 = pcVar4 + 1;
      } while (cVar2 != '\0');
    }
    else {
      iVar6 = (int)resName - (int)param_1;
      if (param_3 == 1) {
        do {
          cVar3 = *param_1;
          param_1[iVar6] = cVar3;
          param_1 = param_1 + 1;
        } while (cVar3 != '\0');
        resName[param_4] = cVar2;
      }
      else {
        do {
          cVar2 = *param_1;
          param_1[iVar6] = cVar2;
          param_1 = param_1 + 1;
        } while (cVar2 != '\0');
      }
    }
    pcVar4 = param_2;
    if (param_2 != (char *)0x0) {
      do {
        cVar2 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar2 != '\0');
      uVar5 = (int)pcVar4 - (int)param_2;
      pcVar4 = (char *)((int)&cnt + 3);
      do {
        pcVar1 = pcVar4 + 1;
        pcVar4 = pcVar4 + 1;
      } while (*pcVar1 != '\0');
      for (uVar7 = uVar5 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pcVar4 = *(undefined4 *)param_2;
        param_2 = param_2 + 4;
        pcVar4 = pcVar4 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar4 = *param_2;
        param_2 = param_2 + 1;
        pcVar4 = pcVar4 + 1;
      }
    }
    pcVar4 = resName;
  }
  return pcVar4;
}

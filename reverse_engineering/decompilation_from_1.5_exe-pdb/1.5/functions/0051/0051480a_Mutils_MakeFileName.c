/*
 * Entry: 0051480a
 * Name: Mutils_MakeFileName
 * Namespace: Global
 * Signature: void Mutils_MakeFileName(char * param_1, char * param_2, char * param_3, char * param_4, char * param_5, char * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Mutils_MakeFileName(char *param_1,char *param_2,char *param_3,char *param_4,char *param_5,
                   char *param_6)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  int iVar6;
  char *pcVar7;
  
  *param_1 = '\0';
  if ((param_2 != (char *)0x0) && (*param_2 != '\0')) {
    iVar6 = (int)param_1 - (int)param_2;
    do {
      cVar1 = *param_2;
      param_2[iVar6] = cVar1;
      param_2 = param_2 + 1;
    } while (cVar1 != '\0');
  }
  if ((param_3 != (char *)0x0) && (*param_3 != '\0')) {
    pcVar2 = param_3;
    pcVar7 = param_1;
    if (*param_1 != '\0') {
      do {
        pcVar5 = pcVar7;
        pcVar7 = pcVar5 + 1;
      } while (*pcVar5 != '\0');
      pcVar7 = param_1;
      if (pcVar5[-1] != '\\') {
        do {
          pcVar5 = pcVar7;
          pcVar7 = pcVar5 + 1;
        } while (*pcVar5 != '\0');
        if (pcVar5[-1] != ':') {
          pcVar7 = param_1 + -1;
          do {
            pcVar5 = pcVar7 + 1;
            pcVar7 = pcVar7 + 1;
          } while (*pcVar5 != '\0');
          *(char (*) [2])pcVar7 = (char  [2])0x5c;
        }
      }
    }
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    uVar3 = (int)pcVar2 - (int)param_3;
    pcVar2 = param_1 + -1;
    do {
      pcVar7 = pcVar2 + 1;
      pcVar2 = pcVar2 + 1;
    } while (*pcVar7 != '\0');
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar2 = *(undefined4 *)param_3;
      param_3 = param_3 + 4;
      pcVar2 = pcVar2 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar2 = *param_3;
      param_3 = param_3 + 1;
      pcVar2 = pcVar2 + 1;
    }
  }
  if ((param_4 != (char *)0x0) && (*param_4 != '\0')) {
    pcVar2 = param_4;
    pcVar7 = param_1;
    if (*param_1 != '\0') {
      do {
        pcVar5 = pcVar7;
        pcVar7 = pcVar5 + 1;
      } while (*pcVar5 != '\0');
      pcVar7 = param_1;
      if (pcVar5[-1] != '\\') {
        do {
          pcVar5 = pcVar7;
          pcVar7 = pcVar5 + 1;
        } while (*pcVar5 != '\0');
        if (pcVar5[-1] != ':') {
          pcVar7 = param_1 + -1;
          do {
            pcVar5 = pcVar7 + 1;
            pcVar7 = pcVar7 + 1;
          } while (*pcVar5 != '\0');
          *(char (*) [2])pcVar7 = (char  [2])0x5c;
        }
      }
    }
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    uVar3 = (int)pcVar2 - (int)param_4;
    pcVar2 = param_1 + -1;
    do {
      pcVar7 = pcVar2 + 1;
      pcVar2 = pcVar2 + 1;
    } while (*pcVar7 != '\0');
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar2 = *(undefined4 *)param_4;
      param_4 = param_4 + 4;
      pcVar2 = pcVar2 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar2 = *param_4;
      param_4 = param_4 + 1;
      pcVar2 = pcVar2 + 1;
    }
  }
  if ((param_5 != (char *)0x0) && (*param_5 != '\0')) {
    pcVar2 = param_5;
    pcVar7 = param_1;
    if (*param_1 != '\0') {
      do {
        pcVar5 = pcVar7;
        pcVar7 = pcVar5 + 1;
      } while (*pcVar5 != '\0');
      pcVar7 = param_1;
      if (pcVar5[-1] != '\\') {
        do {
          pcVar5 = pcVar7;
          pcVar7 = pcVar5 + 1;
        } while (*pcVar5 != '\0');
        if (pcVar5[-1] != ':') {
          pcVar7 = param_1 + -1;
          do {
            pcVar5 = pcVar7 + 1;
            pcVar7 = pcVar7 + 1;
          } while (*pcVar5 != '\0');
          *(char (*) [2])pcVar7 = (char  [2])0x5c;
        }
      }
    }
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    uVar3 = (int)pcVar2 - (int)param_5;
    pcVar2 = param_1 + -1;
    do {
      pcVar7 = pcVar2 + 1;
      pcVar2 = pcVar2 + 1;
    } while (*pcVar7 != '\0');
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar2 = *(undefined4 *)param_5;
      param_5 = param_5 + 4;
      pcVar2 = pcVar2 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar2 = *param_5;
      param_5 = param_5 + 1;
      pcVar2 = pcVar2 + 1;
    }
  }
  pcVar2 = param_6;
  if (param_6 != (char *)0x0) {
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    uVar3 = (int)pcVar2 - (int)param_6;
    pcVar2 = param_1 + -1;
    do {
      pcVar7 = pcVar2 + 1;
      pcVar2 = pcVar2 + 1;
    } while (*pcVar7 != '\0');
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar2 = *(undefined4 *)param_6;
      param_6 = param_6 + 4;
      pcVar2 = pcVar2 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar2 = *param_6;
      param_6 = param_6 + 1;
      pcVar2 = pcVar2 + 1;
    }
  }
  return;
}

/*
 * Entry: 0050edb7
 * Name: check_type_cast
 * Namespace: Global
 * Signature: int check_type_cast(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl check_type_cast(char *param_1)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  bool bVar4;
  
  iVar1 = 4;
  bVar4 = true;
  pcVar3 = param_1;
  pcVar2 = "int";
  do {
    if (iVar1 == 0) break;
    iVar1 = iVar1 + -1;
    bVar4 = *pcVar3 == *pcVar2;
    pcVar3 = pcVar3 + 1;
    pcVar2 = pcVar2 + 1;
  } while (bVar4);
  if (!bVar4) {
    iVar1 = 5;
    bVar4 = true;
    pcVar3 = param_1;
    pcVar2 = "char";
    do {
      if (iVar1 == 0) break;
      iVar1 = iVar1 + -1;
      bVar4 = *pcVar3 == *pcVar2;
      pcVar3 = pcVar3 + 1;
      pcVar2 = pcVar2 + 1;
    } while (bVar4);
    if (!bVar4) {
      iVar1 = 5;
      bVar4 = true;
      pcVar3 = param_1;
      pcVar2 = "long";
      do {
        if (iVar1 == 0) break;
        iVar1 = iVar1 + -1;
        bVar4 = *pcVar3 == *pcVar2;
        pcVar3 = pcVar3 + 1;
        pcVar2 = pcVar2 + 1;
      } while (bVar4);
      if (!bVar4) {
        iVar1 = 6;
        bVar4 = true;
        pcVar3 = param_1;
        pcVar2 = "float";
        do {
          if (iVar1 == 0) break;
          iVar1 = iVar1 + -1;
          bVar4 = *pcVar3 == *pcVar2;
          pcVar3 = pcVar3 + 1;
          pcVar2 = pcVar2 + 1;
        } while (bVar4);
        if (bVar4) {
          return 2;
        }
        bVar4 = true;
        pcVar3 = "Adouble";
        iVar1 = 7;
        do {
          pcVar3 = pcVar3 + 1;
          if (iVar1 == 0) break;
          iVar1 = iVar1 + -1;
          bVar4 = *param_1 == *pcVar3;
          param_1 = param_1 + 1;
        } while (bVar4);
        return !bVar4 - 1 & 2;
      }
    }
  }
  return 1;
}

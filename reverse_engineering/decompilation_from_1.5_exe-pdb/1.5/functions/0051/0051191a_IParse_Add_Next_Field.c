/*
 * Entry: 0051191a
 * Name: IParse_Add_Next_Field
 * Namespace: Global
 * Signature: int IParse_Add_Next_Field(_struct_list_element * param_1, int * param_2, int param_3, int * param_4, char[80] * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
IParse_Add_Next_Field
          (_struct_list_element *param_1,int *param_2,int param_3,int *param_4,char (*param_5) [80])

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  bool bVar5;
  int iVar6;
  
  iVar6 = *param_2;
  pcVar2 = param_5[iVar6];
  iVar1 = 5;
  bVar5 = true;
  pcVar4 = pcVar2;
  pcVar3 = "char";
  do {
    if (iVar1 == 0) break;
    iVar1 = iVar1 + -1;
    bVar5 = *pcVar4 == *pcVar3;
    pcVar4 = pcVar4 + 1;
    pcVar3 = pcVar3 + 1;
  } while (bVar5);
  if (bVar5) {
    iVar1 = 2;
    bVar5 = true;
    pcVar2 = param_5[iVar6 + 2];
    pcVar4 = "[";
    do {
      if (iVar1 == 0) break;
      iVar1 = iVar1 + -1;
      bVar5 = *pcVar2 == *pcVar4;
      pcVar2 = pcVar2 + 1;
      pcVar4 = pcVar4 + 1;
    } while (bVar5);
    if (bVar5) {
      iVar6 = param_4[iVar6 + 3];
      iVar1 = 10;
    }
    else {
      iVar6 = 1;
      iVar1 = 4;
    }
  }
  else {
    iVar6 = 4;
    bVar5 = true;
    pcVar4 = pcVar2;
    pcVar3 = "int";
    do {
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      bVar5 = *pcVar4 == *pcVar3;
      pcVar4 = pcVar4 + 1;
      pcVar3 = pcVar3 + 1;
    } while (bVar5);
    if (bVar5) {
      iVar6 = 4;
      iVar1 = 1;
    }
    else {
      iVar6 = 6;
      bVar5 = true;
      pcVar4 = pcVar2;
      pcVar3 = "float";
      do {
        if (iVar6 == 0) break;
        iVar6 = iVar6 + -1;
        bVar5 = *pcVar4 == *pcVar3;
        pcVar4 = pcVar4 + 1;
        pcVar3 = pcVar3 + 1;
      } while (bVar5);
      if (bVar5) {
        iVar6 = 4;
        iVar1 = 2;
      }
      else {
        pcVar4 = "Adouble";
        iVar6 = 7;
        bVar5 = true;
        do {
          pcVar4 = pcVar4 + 1;
          if (iVar6 == 0) break;
          iVar6 = iVar6 + -1;
          bVar5 = *pcVar2 == *pcVar4;
          pcVar2 = pcVar2 + 1;
        } while (bVar5);
        if (!bVar5) goto LAB_005119bd;
        iVar6 = 8;
        iVar1 = 3;
      }
    }
  }
  IParse_Append_Field_To_Structure(param_1,param_2,param_3,param_5,iVar1,iVar6);
LAB_005119bd:
  return *param_2;
}

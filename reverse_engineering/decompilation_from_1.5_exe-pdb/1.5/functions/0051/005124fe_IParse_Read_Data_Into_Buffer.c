/*
 * Entry: 005124fe
 * Name: IParse_Read_Data_Into_Buffer
 * Namespace: Global
 * Signature: void IParse_Read_Data_Into_Buffer(char * param_1, int param_2, char * * param_3, int * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl IParse_Read_Data_Into_Buffer(char *param_1,int param_2,char **param_3,int *param_4)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  char cVar8;
  
  iVar5 = param_2;
  bVar2 = false;
  bVar3 = false;
  bVar1 = false;
  bVar4 = false;
  pcVar6 = calloc(1,param_2);
  *param_3 = pcVar6;
  if (pcVar6 == (char *)0x0) {
    IParse_Report("Unable to allocate memory for buffer while preprocessing script",2);
  }
  pcVar6 = *param_3;
  param_2 = (int)param_1;
LAB_00512544:
  while( true ) {
    if ((uint)param_2 < param_1 + iVar5) {
      cVar8 = *(char *)param_2;
      param_2 = param_2 + 1;
    }
    else {
      cVar8 = -1;
    }
    iVar7 = IParse_Find_Char_Type(cVar8);
    if (!bVar1) break;
    bVar1 = false;
    if (cVar8 != '/') {
      if (cVar8 == '*') {
        bVar3 = true;
      }
      else {
        *pcVar6 = '/';
        pcVar6 = pcVar6 + 1;
        bVar2 = false;
        bVar3 = false;
      }
      break;
    }
    bVar2 = true;
  }
  if (bVar2) {
    if ((cVar8 != '\n') && (cVar8 != '\r')) goto LAB_00512544;
    bVar2 = false;
  }
  else {
    if (bVar3) {
      if (bVar4) {
        if (cVar8 == '/') {
          bVar3 = false;
          goto LAB_00512544;
        }
        bVar4 = false;
      }
      if (cVar8 == '*') {
        bVar4 = true;
      }
      goto LAB_00512544;
    }
    if (iVar7 == 2) {
      if (cVar8 == '/') {
        bVar1 = true;
        goto LAB_00512544;
      }
    }
    else if (iVar7 == 3) {
      *param_4 = (int)pcVar6 - (int)*param_3;
      return;
    }
  }
  *pcVar6 = cVar8;
  pcVar6 = pcVar6 + 1;
  goto LAB_00512544;
}

/*
 * Entry: 00511a18
 * Name: IParse_Fill_Individual_Field
 * Namespace: Global
 * Signature: int IParse_Fill_Individual_Field(_domain * param_1, char * param_2, int param_3, int * param_4, double * param_5, char[80] * param_6, int * param_7, int * param_8)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
IParse_Fill_Individual_Field
          (_domain *param_1,char *param_2,int param_3,int *param_4,double *param_5,
          char (*param_6) [80],int *param_7,int *param_8)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  double *pdVar4;
  char (*pacVar5) [80];
  int *piVar6;
  char *pcVar7;
  int iVar8;
  double dVar9;
  
  piVar6 = param_8;
  pacVar5 = param_6;
  pdVar4 = param_5;
  iVar3 = *param_8;
  for (iVar8 = iVar3; (param_6[iVar8][0] != ';' && (param_6[iVar8][0] != ',')); iVar8 = iVar8 + 1) {
  }
  if (param_3 == 1) {
    expression(param_1,iVar3,iVar8 + -1,param_4,param_5,param_6,param_7,&param_3,(int *)&param_8,
               (int *)&param_6);
    *(int **)param_2 = param_8;
  }
  else if (param_3 == 2) {
    dVar9 = expression(param_1,iVar3,iVar8 + -1,param_4,param_5,param_6,param_7,&param_3,
                       (int *)&param_8,(int *)&param_6);
    *(float *)param_2 = (float)dVar9;
  }
  else {
    if (param_3 != 3) {
      if (param_3 == 4) {
        *param_8 = iVar3 + 1;
        *param_2 = param_6[iVar3 + 1][0];
        *param_8 = *param_8 + 3;
        return 0;
      }
      if (param_3 == 10) {
        pcVar1 = param_6[iVar3];
        pcVar7 = pcVar1;
        do {
          cVar2 = *pcVar7;
          pcVar7 = pcVar7 + 1;
        } while (cVar2 != '\0');
        strncpy(param_2,pcVar1 + 1,(size_t)(pcVar7 + (-2 - (int)(pcVar1 + 1))));
        pcVar7 = pacVar5[*piVar6];
        pcVar1 = pcVar7 + 1;
        do {
          cVar2 = *pcVar7;
          pcVar7 = pcVar7 + 1;
        } while (cVar2 != '\0');
        param_2[(int)(pcVar7 + (-2 - (int)pcVar1))] = '\0';
        *piVar6 = *piVar6 + 2;
        return 0;
      }
      return -1;
    }
    expression(param_1,iVar3,iVar8 + -1,param_4,param_5,param_6,param_7,&param_3,(int *)&param_8,
               (int *)&param_6);
    iVar3 = *piVar6;
    *(undefined4 *)param_2 = *(undefined4 *)(pdVar4 + iVar3);
    *(undefined4 *)(param_2 + 4) = *(undefined4 *)((int)pdVar4 + iVar3 * 8 + 4);
  }
  *piVar6 = iVar8 + 1;
  return 0;
}

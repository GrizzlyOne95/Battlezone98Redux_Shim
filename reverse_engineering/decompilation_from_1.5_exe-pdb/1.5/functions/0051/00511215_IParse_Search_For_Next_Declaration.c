/*
 * Entry: 00511215
 * Name: IParse_Search_For_Next_Declaration
 * Namespace: Global
 * Signature: int IParse_Search_For_Next_Declaration(char * param_1, int * param_2, int param_3, _domain * param_4, char * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
IParse_Search_For_Next_Declaration
          (char *param_1,int *param_2,int param_3,_domain *param_4,char *param_5)

{
  int iVar1;
  
  iVar1 = IParse_Read_Next_String(param_1,param_2,param_3,param_5);
  if (iVar1 == -1) {
    return -1;
  }
  iVar1 = IParse_Variable_Match(param_4,param_5);
  return iVar1;
}

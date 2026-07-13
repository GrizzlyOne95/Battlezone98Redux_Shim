/*
 * Entry: 0051133d
 * Name: IParse_Append_Quote_Char
 * Namespace: Global
 * Signature: void IParse_Append_Quote_Char(char * * param_1, int * param_2, char param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl IParse_Append_Quote_Char(char **param_1,int *param_2,char param_3)

{
  char *pcVar1;
  
  (*param_1)[*param_2] = param_3;
  *param_2 = *param_2 + 1;
  pcVar1 = realloc(*param_1,*param_2 + 1);
  *param_1 = pcVar1;
  return;
}

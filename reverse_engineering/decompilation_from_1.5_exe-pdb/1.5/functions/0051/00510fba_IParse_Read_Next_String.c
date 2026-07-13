/*
 * Entry: 00510fba
 * Name: IParse_Read_Next_String
 * Namespace: Global
 * Signature: int IParse_Read_Next_String(char * param_1, int * param_2, int param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IParse_Read_Next_String(char *param_1,int *param_2,int param_3,char *param_4)

{
  int iVar1;
  char local_8;
  
  local_8 = '\x14';
  iVar1 = IParse_Find_Char_Type('\x14');
  if (iVar1 == 0) {
    do {
      local_8 = param_1[*param_2];
      iVar1 = *param_2 + 1;
      *param_2 = iVar1;
      if (param_3 < iVar1) {
        return -1;
      }
      iVar1 = IParse_Find_Char_Type(local_8);
    } while (iVar1 == 0);
    if (local_8 == '#') {
      *param_4 = '#';
      local_8 = param_1[*param_2];
      param_4 = param_4 + 1;
      iVar1 = *param_2 + 1;
      *param_2 = iVar1;
      if (param_3 < iVar1) {
        return -1;
      }
    }
    if (local_8 == '{') {
      *param_4 = '{';
      param_4 = param_4 + 1;
      *param_2 = *param_2 + 1;
      if (param_3 < *param_2) {
        return -1;
      }
      goto LAB_00511052;
    }
  }
  while (iVar1 = IParse_Find_Char_Type(local_8), iVar1 == 1) {
    *param_4 = local_8;
    local_8 = param_1[*param_2];
    param_4 = param_4 + 1;
    iVar1 = *param_2 + 1;
    *param_2 = iVar1;
    if (param_3 < iVar1) {
      return -1;
    }
  }
LAB_00511052:
  *param_2 = *param_2 + -1;
  *param_4 = '\0';
  return 1;
}

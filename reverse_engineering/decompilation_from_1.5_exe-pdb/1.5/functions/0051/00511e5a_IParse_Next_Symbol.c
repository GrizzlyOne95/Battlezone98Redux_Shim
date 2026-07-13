/*
 * Entry: 00511e5a
 * Name: IParse_Next_Symbol
 * Namespace: Global
 * Signature: int IParse_Next_Symbol(char * param_1, int * param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IParse_Next_Symbol(char *param_1,int *param_2,char *param_3)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  uint local_c;
  int local_8;
  
  local_8 = 4;
  if (param_1[*param_2] == ' ') {
    *param_2 = *param_2 + 1;
  }
  iVar3 = isdigit((int)param_1[*param_2]);
  if (iVar3 != 0) {
    local_8 = 1;
  }
  local_c = (uint)(iVar3 != 0);
  if (param_1[*param_2] == '\"') {
    *param_3 = '\"';
    *param_2 = *param_2 + 1;
    iVar3 = *param_2;
    cVar1 = param_1[iVar3];
    pcVar2 = param_3;
    while ((param_3 = pcVar2 + 1, cVar1 != '\0' && (param_1[iVar3] != '\"'))) {
      *param_3 = param_1[iVar3];
      *param_2 = *param_2 + 1;
      iVar3 = *param_2;
      cVar1 = param_1[iVar3];
      pcVar2 = param_3;
    }
    if (param_1[iVar3] == '\"') {
      *param_3 = '\"';
      *param_2 = *param_2 + 1;
      param_3 = pcVar2 + 2;
    }
  }
  else {
    iVar3 = IParse_Find_Char_Type(param_1[*param_2]);
    while (iVar3 != 0) {
      iVar3 = isdigit((int)param_1[*param_2]);
      if ((iVar3 == 0) && (param_1[*param_2] != '.')) {
        local_c = 0xffffffff;
        local_8 = 4;
      }
      if (local_c != 0xffffffff) {
        if ((local_8 == 3) && (param_1[*param_2] == '.')) {
          local_c = 0xffffffff;
          local_8 = 4;
        }
        else if (param_1[*param_2] == '.') {
          local_8 = 3;
        }
      }
      *param_3 = param_1[*param_2];
      *param_2 = *param_2 + 1;
      param_3 = param_3 + 1;
      iVar3 = IParse_Find_Char_Type(param_1[*param_2]);
    }
  }
  *param_3 = '\0';
  if (param_1[*param_2] != '\0') {
    *param_2 = *param_2 + 1;
  }
  return local_8;
}

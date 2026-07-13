/*
 * Entry: 004bb65f
 * Name: get_discrete_num
 * Namespace: Global
 * Signature: int get_discrete_num(int param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl get_discrete_num(int param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = isdigit((int)*param_2);
  if (iVar1 != 0) {
    iVar1 = atoi(param_2);
    return iVar1;
  }
  if (param_1 != -1) {
    if (input_desc[param_1].discrete_names == (char **)0x0) {
      DEBUG_systemWarning("%s line %d: no discrete input channel named \"%s\".");
    }
    else {
      iVar1 = 0;
      if (0 < input_desc[param_1].num_discrete) {
        do {
          if ((input_desc[param_1].discrete_names[iVar1] != (char *)0x0) &&
             (iVar2 = _stricmp(input_desc[param_1].discrete_names[iVar1],param_2), iVar2 == 0)) {
            return iVar1;
          }
          iVar1 = iVar1 + 1;
        } while (iVar1 < input_desc[param_1].num_discrete);
      }
      InputErrorOkOrCancel(0x6f,param_2,input_desc[param_1].long_name);
    }
  }
  return -1;
}

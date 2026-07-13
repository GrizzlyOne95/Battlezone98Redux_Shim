/*
 * Entry: 0051227a
 * Name: IParse_Get_Termination_String
 * Namespace: Global
 * Signature: char * IParse_Get_Termination_String(int param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl IParse_Get_Termination_String(int param_1,char *param_2)

{
  undefined2 uVar1;
  
  if (param_1 == 5) {
    param_2[0] = '}';
    param_2[1] = ';';
    param_2[2] = '\0';
  }
  else {
    if (param_1 == 7) {
      uVar1 = 10;
    }
    else {
      if (param_1 == 8) {
        builtin_strncpy(param_2,"#END_DATA",10);
        return param_2;
      }
      if ((param_1 == 0xb) || (param_1 == 0xc)) {
        uVar1 = 0x29;
      }
      else if (param_1 == 0xd) {
        uVar1 = 0x7d;
      }
      else if (param_1 == 0x10) {
        uVar1 = 10;
      }
      else {
        uVar1 = 0x3b;
      }
    }
    *(undefined2 *)param_2 = uVar1;
  }
  return param_2;
}

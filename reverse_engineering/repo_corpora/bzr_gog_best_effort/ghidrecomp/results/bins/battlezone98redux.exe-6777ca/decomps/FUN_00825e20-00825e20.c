
uint FUN_00825e20(char *param_1,char *param_2)

{
  char *pcVar1;
  bool bVar2;
  uint uVar3;
  char *pcVar4;
  bool bVar5;
  uint local_30;
  int local_18;
  
  do {
    if (*param_2 == '\0') {
      local_30 = (uint)(*param_1 == '\0');
      return local_30;
    }
    if (*param_1 == '\0') {
      if ((*param_2 == '*') && (param_2[1] == '\0')) {
        return 1;
      }
      return 0xffffffff;
    }
    switch(*param_2) {
    case '*':
      if (param_2[1] != '\0') {
        uVar3 = FUN_00825de0(param_1,param_2 + 1);
        return uVar3;
      }
      return 1;
    default:
switchD_00825eaa_caseD_2b:
      if (*param_1 != *param_2) {
        return 0;
      }
      break;
    case '?':
      break;
    case '[':
      pcVar1 = param_2 + 1;
      if (*pcVar1 == '!') {
        param_2 = param_2 + 1;
      }
      local_18 = 0x100;
      bVar2 = false;
      while ((pcVar4 = param_2 + 1, *pcVar4 != '\0' && (*pcVar4 != ']'))) {
        if (*pcVar4 == '-') {
          param_2 = param_2 + 2;
          if ((*param_2 < *param_1) || (*param_1 < local_18)) {
            bVar5 = false;
          }
          else {
            bVar5 = true;
          }
        }
        else {
          bVar5 = *param_1 == *pcVar4;
          param_2 = pcVar4;
        }
        if (bVar5) {
          bVar2 = true;
        }
        local_18 = (int)*param_2;
      }
      param_2 = pcVar4;
      if (bVar2 == (*pcVar1 == '!')) {
        return 0;
      }
      break;
    case '\\':
      param_2 = param_2 + 1;
      if (*param_2 != '\0') goto switchD_00825eaa_caseD_2b;
    }
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
  } while( true );
}


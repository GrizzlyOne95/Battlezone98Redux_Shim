
undefined4 FUN_00431170(int *param_1,undefined4 param_2,char *param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 extraout_var;
  char *local_c;
  char local_5;
  
  local_5 = *param_3;
  while( true ) {
    if (local_5 == '\0') {
      return 1;
    }
    for (local_c = param_3; (*local_c != '\0' && (*local_c != '\n')); local_c = local_c + 1) {
    }
    local_5 = *local_c;
    *local_c = '\0';
    cVar1 = FUN_004306d0(param_3);
    if (cVar1 == '\0') break;
    *local_c = local_5;
    param_3 = local_c + 1;
    uVar2 = ~<>(extraout_var);
    (**(code **)(*param_1 + 4))(uVar2);
    (**(code **)(*param_1 + 4))(&DAT_00871530);
  }
  return 0;
}


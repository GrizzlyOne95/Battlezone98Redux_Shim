
undefined4 FUN_0046ced0(undefined4 param_1,char *param_2)

{
  int local_c;
  
  if (param_2 == (char *)0x0) {
    local_c = -1;
  }
  else {
    local_c = atoi(param_2);
  }
  if ((0 < local_c) && (local_c < 0x10)) {
    if (DAT_00917398 == 0) {
      FUN_0046ce50(local_c,0);
      FUN_004dfe30(local_c);
      FUN_00572da0("UnAlly with team %d",local_c);
    }
    else {
      FUN_0046ce50(local_c,1);
      FUN_004dfdf0(local_c);
      FUN_00572da0("Ally with team %d",local_c);
    }
  }
  FUN_00823330(DAT_0260d184,0);
  FUN_00823390(DAT_0260d184,0);
  return 1;
}


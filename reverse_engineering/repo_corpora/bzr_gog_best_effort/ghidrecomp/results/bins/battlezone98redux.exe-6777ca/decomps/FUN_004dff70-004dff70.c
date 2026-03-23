
void __thiscall FUN_004dff70(int param_1,char *param_2,int param_3)

{
  char cVar1;
  char *local_10;
  
  if (*param_2 == '\0') {
    operator_delete(*(void **)(param_1 + 0xe8));
    *(undefined4 *)(param_1 + 0xe8) = 0;
  }
  else {
    FUN_004d9630(param_2);
  }
  local_10 = param_2;
  do {
    cVar1 = *local_10;
    local_10 = local_10 + 1;
  } while (cVar1 != '\0');
  FUN_00422c10(param_2 + (int)(local_10 + (1 - (int)(param_2 + 1))),
               param_3 - (int)(local_10 + (1 - (int)(param_2 + 1))));
  return;
}


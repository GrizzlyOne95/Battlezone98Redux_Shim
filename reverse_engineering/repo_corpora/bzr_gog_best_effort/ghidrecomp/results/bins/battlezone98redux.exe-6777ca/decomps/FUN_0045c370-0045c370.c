
char FUN_0045c370(undefined4 param_1,undefined4 *param_2,int param_3)

{
  char cVar1;
  undefined4 local_c [2];
  
  local_c[0] = *param_2;
  if (param_3 == 4) {
    cVar1 = FUN_004ce400(param_1,local_c,4);
    if (cVar1 != '\0') {
      *param_2 = local_c[0];
    }
  }
  else {
    cVar1 = '\0';
  }
  return cVar1;
}


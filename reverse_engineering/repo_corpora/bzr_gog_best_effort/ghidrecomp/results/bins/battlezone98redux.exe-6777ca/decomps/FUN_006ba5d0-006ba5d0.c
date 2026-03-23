
undefined4 FUN_006ba5d0(undefined4 param_1,int param_2)

{
  char cVar1;
  undefined4 local_c;
  int local_8;
  
  cVar1 = FUN_006ba440(param_1);
  if (cVar1 == '\0') {
    local_c = 0;
  }
  else {
    local_8 = FUN_006ba4c0(param_1);
    FUN_006da2a0(param_2 + local_8,param_2 + 4 + local_8,&local_c);
  }
  return local_c;
}


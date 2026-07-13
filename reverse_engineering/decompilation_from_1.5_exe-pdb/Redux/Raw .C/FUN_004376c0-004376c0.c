
undefined4 FUN_004376c0(int param_1,int param_2,undefined4 param_3)

{
  int *piVar1;
  undefined4 local_c;
  
  local_c = 0;
  if (param_2 == 0) {
    piVar1 = (int *)FUN_0062c840();
    if (piVar1 == (int *)0x0) {
      return 0;
    }
    param_2 = *piVar1;
    if (param_2 == 0) {
      return 0;
    }
  }
  if (param_1 != 0) {
    local_c = FUN_0043aa30(param_1,param_2,param_3,0);
  }
  return local_c;
}


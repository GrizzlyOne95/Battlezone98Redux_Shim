
void FUN_00836056(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  if (param_2 < param_1[3]) {
    iVar1 = param_1[param_2 * 2 + 5];
    if (iVar1 == -1) {
      FUN_0082bc39(param_1[2],"unfinished capture");
    }
    if (iVar1 == -2) {
      FUN_0082ccca(param_1[2],(param_1[param_2 * 2 + 4] - *param_1) + 1);
    }
    else {
      FUN_0082cd08(param_1[2],param_1[param_2 * 2 + 4],iVar1);
    }
  }
  else if (param_2 == 0) {
    FUN_0082cd08(param_1[2],param_3,param_4 - param_3);
  }
  else {
    FUN_0082bc39(param_1[2],"invalid capture index");
  }
  return;
}


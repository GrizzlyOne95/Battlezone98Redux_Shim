
void FUN_00831758(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  
  if (param_3[4] == 0) {
    uVar1 = (*(code *)param_3[1])(*param_3,param_1,param_2,param_3[2]);
    param_3[4] = uVar1;
  }
  return;
}


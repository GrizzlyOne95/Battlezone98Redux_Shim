
void FUN_0083a089(int *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  if (*(int *)(*param_1 + 0x3c) == 0) {
    uVar1 = FUN_0082e8cd(param_1[4],"main function has more than %d %s");
  }
  else {
    uVar1 = FUN_0082e8cd(param_1[4],"function at line %d has more than %d %s",
                         *(int *)(*param_1 + 0x3c),param_2,param_3);
  }
  FUN_00838ef5(param_1[3],uVar1,0);
  return;
}


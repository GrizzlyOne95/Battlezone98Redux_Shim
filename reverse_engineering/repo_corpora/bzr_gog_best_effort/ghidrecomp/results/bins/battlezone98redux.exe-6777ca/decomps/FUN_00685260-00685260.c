
void FUN_00685260(int *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  if (param_1 != (int *)0x0) {
    uVar1 = (**(code **)(*param_1 + 0x54))();
    FUN_006786f0(uVar1);
    (**(code **)(*param_1 + 100))();
    if (param_1 == (int *)0x0) {
      uVar2 = 0;
    }
    else {
      uVar2 = (**(code **)*param_1)(1);
    }
    (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x15c))(uVar1,uVar1,uVar2);
  }
  return;
}


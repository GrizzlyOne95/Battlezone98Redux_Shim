
void __thiscall FUN_004a6c70(int param_1,int *param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  if (param_2 != (int *)0x0) {
    cVar1 = (**(code **)(*param_2 + 0x38))();
    if (cVar1 != '\0') {
      FUN_0049f3c0(1);
      uVar2 = FUN_00462380();
      *(undefined4 *)(param_1 + 0x1c + *(int *)(param_1 + 0x188) * 4) = uVar2;
      *(int *)(param_1 + 0x188) = *(int *)(param_1 + 0x188) + 1;
    }
  }
  return;
}


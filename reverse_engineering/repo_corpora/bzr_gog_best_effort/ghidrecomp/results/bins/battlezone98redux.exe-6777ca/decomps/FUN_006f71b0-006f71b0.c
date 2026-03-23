
void __thiscall FUN_006f71b0(undefined4 param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  if (*(int *)(param_2 + 0x10) == 0) {
    Set(0);
  }
  else {
    cVar1 = Local(param_1);
    if (cVar1 == '\0') {
      Set(*(undefined4 *)(param_2 + 0x10));
      Set(0);
    }
    else {
      uVar2 = (**(code **)(**(int **)(param_2 + 0x10) + 4))(param_1);
      Set(uVar2);
      Tidy();
    }
  }
  return;
}


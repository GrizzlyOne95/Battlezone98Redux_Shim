
void __thiscall FUN_007c45d0(int param_1,char param_2)

{
  char cVar1;
  
  cVar1 = FUN_007d3360();
  if (cVar1 != param_2) {
    FUN_007d3310(param_2);
    (**(code **)(**(int **)(param_1 + 0x150) + 0x24))(param_2);
    (**(code **)(**(int **)(param_1 + 0x148) + 0x24))(param_2);
    FUN_007cc5c0(param_2);
    (**(code **)(**(int **)(param_1 + 0x14c) + 0x24))(param_2);
    FUN_007cc5c0(param_2);
    FUN_007c46d0();
  }
  return;
}


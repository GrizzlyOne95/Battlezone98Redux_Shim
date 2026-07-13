
void __fastcall FUN_0049e9f0(int param_1)

{
  undefined4 uVar1;
  
  if (*(undefined4 **)(param_1 + 0x38) == (undefined4 *)0x0) {
    uVar1 = 0;
  }
  else {
    uVar1 = (**(code **)**(undefined4 **)(param_1 + 0x38))(1);
  }
  *(undefined4 *)(param_1 + 0x38) = 0;
  (**(code **)(**(int **)(param_1 + 0x34) + 100))(uVar1);
  return;
}



void __thiscall FUN_007c4530(int param_1,char param_2)

{
  undefined4 uVar1;
  
  *(char *)(param_1 + 0x155) = param_2;
  if (param_2 == '\0') {
    uVar1 = FUN_0081cb40("option_box",&DAT_008865a8);
    (**(code **)(**(int **)(param_1 + 0x148) + 0x3c))(uVar1);
  }
  else {
    uVar1 = FUN_0081cb40("option_box",&DAT_00886520);
    (**(code **)(**(int **)(param_1 + 0x148) + 0x3c))(uVar1);
  }
  uVar1 = FUN_007ccaf0();
  FUN_007cca20(uVar1);
  return;
}


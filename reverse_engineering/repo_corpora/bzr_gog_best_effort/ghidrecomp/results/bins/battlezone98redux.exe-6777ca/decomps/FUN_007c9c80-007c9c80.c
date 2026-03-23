
void __thiscall FUN_007c9c80(int param_1,char param_2)

{
  int iVar1;
  
  iVar1 = FUN_00822e60();
  if ((param_2 != '\0') || (-1 < iVar1 - *(int *)(param_1 + 0x144))) {
    *(int *)(param_1 + 0x144) = iVar1 + 100;
    FUN_005d50a0();
    FUN_00618bc0();
  }
  return;
}


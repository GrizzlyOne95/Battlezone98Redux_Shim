
void __thiscall FUN_007a3c30(int param_1,char param_2)

{
  float10 fVar1;
  
  if (param_2 != *(char *)(param_1 + 0x48)) {
    if (param_2 == '\0') {
      (**(code **)(**(int **)(param_1 + 0x2c) + 0x24))(0);
      fVar1 = (float10)FUN_007d37d0(1);
      fVar1 = (float10)FUN_007d37b0((float)fVar1);
      (**(code **)(**(int **)(param_1 + 0x44) + 0x28))((float)fVar1 - 1000.0);
    }
    else {
      (**(code **)(**(int **)(param_1 + 0x2c) + 0x24))(1);
      fVar1 = (float10)FUN_007d37d0(1);
      fVar1 = (float10)FUN_007d37b0((float)fVar1);
      (**(code **)(**(int **)(param_1 + 0x44) + 0x28))((float)fVar1 + 1000.0);
    }
    *(char *)(param_1 + 0x48) = param_2;
  }
  return;
}


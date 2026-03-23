
void __fastcall FUN_00605780(int param_1)

{
  char cVar1;
  
  if ((*(int *)(param_1 + 0xb8) != 0) &&
     (cVar1 = (**(code **)(**(int **)(param_1 + 0xb8) + 0x10))(), cVar1 != '\0')) {
    (**(code **)(**(int **)(param_1 + 0xb8) + 0xc))();
  }
  return;
}



void __fastcall FUN_005b6e60(int param_1)

{
  char cVar1;
  
  cVar1 = (**(code **)(**(int **)(param_1 + 0x30) + 0x18))();
  if (cVar1 == '\0') {
    (**(code **)(**(int **)(param_1 + 0x30) + 0x1c))();
  }
  else {
    *(undefined4 *)(param_1 + 0x4c) = 1;
  }
  return;
}


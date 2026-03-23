
bool __fastcall FUN_00475000(int param_1)

{
  char cVar1;
  
  cVar1 = FUN_005af7b0();
  if (cVar1 == '\0') {
    *(undefined4 *)(param_1 + 0x1c) = 3;
  }
  else {
    (**(code **)(**(int **)(param_1 + 0x20) + 0x60))();
    *(undefined4 *)(param_1 + 0x1c) = 2;
  }
  return cVar1 != '\0';
}


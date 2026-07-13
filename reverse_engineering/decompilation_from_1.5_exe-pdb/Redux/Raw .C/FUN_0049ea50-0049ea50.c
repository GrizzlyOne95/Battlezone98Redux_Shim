
void __fastcall FUN_0049ea50(int param_1)

{
  char cVar1;
  
  if (*(int *)(*(int *)(param_1 + 0x38) + 0x14c) == 3) {
    cVar1 = FUN_004723d0();
    if (cVar1 == '\0') {
      FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),0x14,0);
    }
  }
  cVar1 = (**(code **)(**(int **)(param_1 + 0x38) + 0x18))();
  if (cVar1 == '\0') {
    (**(code **)(**(int **)(param_1 + 0x38) + 0x1c))();
  }
  else {
    *(undefined4 *)(param_1 + 0x20) = 3;
  }
  return;
}


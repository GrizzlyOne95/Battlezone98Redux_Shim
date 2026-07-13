
void __fastcall FUN_007c46d0(int param_1)

{
  char cVar1;
  
  cVar1 = FUN_007d3360();
  if ((cVar1 == '\0') || (*(char *)(param_1 + 0x154) == '\0')) {
    (**(code **)(**(int **)(param_1 + 0x144) + 0x24))(0);
  }
  else {
    (**(code **)(**(int **)(param_1 + 0x144) + 0x24))(1);
  }
  return;
}


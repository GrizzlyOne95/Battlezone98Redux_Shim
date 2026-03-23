
void __fastcall FUN_004499f0(int *param_1)

{
  char cVar1;
  
  if (*param_1 != 0) {
    cVar1 = (**(code **)(*(int *)*param_1 + 0x10))();
    if (cVar1 != '\0') {
      *param_1 = 0;
    }
  }
  return;
}


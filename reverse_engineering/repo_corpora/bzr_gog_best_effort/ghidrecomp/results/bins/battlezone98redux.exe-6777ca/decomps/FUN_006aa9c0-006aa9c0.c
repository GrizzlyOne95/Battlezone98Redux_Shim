
uint __fastcall FUN_006aa9c0(uint param_1)

{
  int *piVar1;
  
  if (*(char *)(param_1 + 0xc) == '\0') {
    param_1 = param_1 & 0xffffff00;
  }
  else {
    piVar1 = (int *)FUN_006aa210();
    param_1 = (**(code **)(*piVar1 + 0x54))(1);
  }
  return param_1;
}


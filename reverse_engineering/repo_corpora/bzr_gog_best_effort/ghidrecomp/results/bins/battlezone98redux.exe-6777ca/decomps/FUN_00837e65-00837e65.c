
undefined4 FUN_00837e65(undefined4 param_1)

{
  int *piVar1;
  
  piVar1 = (int *)FUN_0082bbcf(param_1,1,"_LOADLIB");
  if (*piVar1 != 0) {
    FreeLibrary((HMODULE)*piVar1);
  }
  *piVar1 = 0;
  return 0;
}


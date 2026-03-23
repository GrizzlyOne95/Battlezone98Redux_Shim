
undefined4 FUN_00837e92(undefined4 param_1,LPCSTR param_2,LPCSTR param_3)

{
  int *piVar1;
  HMODULE pHVar2;
  FARPROC pFVar3;
  undefined4 uVar4;
  
  piVar1 = (int *)FUN_00837eff(param_1,param_2);
  if (*piVar1 == 0) {
    pHVar2 = LoadLibraryA(param_2);
    if (pHVar2 == (HMODULE)0x0) {
      FUN_008381c0(param_1);
    }
    *piVar1 = (int)pHVar2;
    if (pHVar2 == (HMODULE)0x0) {
      return 1;
    }
  }
  pFVar3 = GetProcAddress((HMODULE)*piVar1,param_3);
  if (pFVar3 == (FARPROC)0x0) {
    FUN_008381c0(param_1);
    uVar4 = 2;
  }
  else {
    FUN_0082cc15(param_1,pFVar3,0);
    uVar4 = 0;
  }
  return uVar4;
}


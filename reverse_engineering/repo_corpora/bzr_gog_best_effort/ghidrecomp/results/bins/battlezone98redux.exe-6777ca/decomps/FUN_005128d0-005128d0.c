
undefined4 __fastcall FUN_005128d0(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  
  iVar2 = FUN_00417ca0(param_1);
  if (iVar2 != 0) {
    piVar3 = (int *)FUN_00417f60(0);
    if ((piVar3 != (int *)0x0) && (cVar1 = (**(code **)(*piVar3 + 0x30))(), cVar1 == '\0')) {
      return 0;
    }
    FUN_004d9880(1);
    FUN_00511fc0();
  }
  return 1;
}



undefined4 __fastcall FUN_006217c0(undefined4 param_1)

{
  int iVar1;
  
  if ((DAT_008ead6c != 0) && (iVar1 = ___scrt_is_ucrt_dll_in_use(param_1), iVar1 == 0)) {
    return 1;
  }
  return 0;
}


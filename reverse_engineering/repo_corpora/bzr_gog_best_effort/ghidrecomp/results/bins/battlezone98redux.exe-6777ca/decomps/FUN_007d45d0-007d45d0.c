
undefined4 __fastcall FUN_007d45d0(int *param_1)

{
  HMODULE pHVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (*param_1 == 0) {
    pHVar1 = LoadLibraryA("RzChromaSDK.dll");
    *param_1 = (int)pHVar1;
    if (*param_1 == 0) {
      return 0;
    }
  }
  if (DAT_009456e0 == (FARPROC)0x0) {
    uVar3 = 0xffffffff;
    DAT_009456e0 = GetProcAddress((HMODULE)*param_1,"Init");
    if ((DAT_009456e0 != (FARPROC)0x0) && (iVar2 = (*DAT_009456e0)(uVar3), iVar2 == 0)) {
      DAT_009456e8 = GetProcAddress((HMODULE)*param_1,"CreateEffect");
      DAT_009456d8 = GetProcAddress((HMODULE)*param_1,"CreateKeyboardEffect");
      DAT_009456f8 = GetProcAddress((HMODULE)*param_1,"CreateMouseEffect");
      DAT_009456f4 = GetProcAddress((HMODULE)*param_1,"CreateHeadsetEffect");
      DAT_009456ec = GetProcAddress((HMODULE)*param_1,"CreateMousepadEffect");
      DAT_009456dc = GetProcAddress((HMODULE)*param_1,"CreateKeypadEffect");
      DAT_009456fc = GetProcAddress((HMODULE)*param_1,"SetEffect");
      DAT_009456f0 = GetProcAddress((HMODULE)*param_1,"DeleteEffect");
      DAT_00945700 = GetProcAddress((HMODULE)*param_1,"QueryDevice");
      if ((((DAT_009456e8 != (FARPROC)0x0) &&
           ((((DAT_009456d8 != (FARPROC)0x0 && (DAT_009456f8 != (FARPROC)0x0)) &&
             (DAT_009456f4 != (FARPROC)0x0)) &&
            ((DAT_009456ec != (FARPROC)0x0 && (DAT_009456dc != (FARPROC)0x0)))))) &&
          (DAT_009456fc != (FARPROC)0x0)) &&
         ((DAT_009456f0 != (FARPROC)0x0 && (DAT_00945700 != (FARPROC)0x0)))) {
        return 1;
      }
      return 0;
    }
  }
  return 1;
}


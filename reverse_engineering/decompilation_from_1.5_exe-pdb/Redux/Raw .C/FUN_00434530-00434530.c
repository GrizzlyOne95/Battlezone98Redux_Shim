
void FUN_00434530(void)

{
  HMODULE hModule;
  FARPROC pFVar1;
  undefined4 uVar2;
  undefined1 local_11c [276];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar2 = 0;
  memset(local_11c,0,0x114);
  hModule = LoadLibraryA("NtDll.dll");
  if (hModule != (HMODULE)0x0) {
    pFVar1 = GetProcAddress(hModule,"RtlGetVersion");
    if (pFVar1 != (FARPROC)0x0) {
      (*pFVar1)(local_11c,pFVar1,uVar2);
    }
    FreeLibrary(hModule);
  }
  FUN_0083e885();
  return;
}


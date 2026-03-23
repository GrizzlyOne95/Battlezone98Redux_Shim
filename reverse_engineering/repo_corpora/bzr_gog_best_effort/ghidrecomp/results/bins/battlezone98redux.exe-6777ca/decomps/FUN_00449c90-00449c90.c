
void __fastcall FUN_00449c90(undefined4 *param_1)

{
  char cVar1;
  DWORD DVar2;
  
  DVar2 = GetCurrentThreadId();
  cVar1 = FUN_00449db0(DVar2);
  if (cVar1 == '\0') {
    FUN_00448bd0();
    LOCK();
    param_1[1] = DVar2;
    UNLOCK();
    *param_1 = 1;
  }
  return;
}


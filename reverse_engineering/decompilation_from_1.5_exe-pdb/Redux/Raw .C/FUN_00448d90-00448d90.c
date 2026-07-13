
void __fastcall FUN_00448d90(uint *param_1)

{
  uint uVar1;
  char cVar2;
  HANDLE hEvent;
  
  LOCK();
  uVar1 = *param_1;
  *param_1 = *param_1 + 0x80000000;
  UNLOCK();
  if (((uVar1 & 0x40000000) == 0) && (-0x80000000 < (int)uVar1)) {
    cVar2 = FUN_00448b40(param_1,0x1e,0x80000000);
    if (cVar2 == '\0') {
      hEvent = (HANDLE)FUN_00448df0();
      SetEvent(hEvent);
    }
  }
  return;
}


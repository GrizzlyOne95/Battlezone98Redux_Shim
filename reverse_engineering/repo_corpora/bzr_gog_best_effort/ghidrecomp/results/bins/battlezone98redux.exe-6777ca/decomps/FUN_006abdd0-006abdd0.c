
DWORD FUN_006abdd0(void)

{
  undefined4 uVar1;
  undefined1 local_14 [8];
  DWORD local_c;
  DWORD local_8;
  
  local_8 = TlsAlloc();
  if (local_8 == 0xffffffff) {
    local_c = GetLastError();
    uVar1 = FUN_006abbb0();
    FUN_00416430(local_c,uVar1);
    FUN_006aba00(local_14,&DAT_0089696c);
  }
  return local_8;
}


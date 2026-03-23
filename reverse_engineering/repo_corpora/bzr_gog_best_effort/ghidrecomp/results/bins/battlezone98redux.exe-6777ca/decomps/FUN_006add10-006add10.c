
void __thiscall FUN_006add10(int param_1,undefined4 param_2)

{
  uint uVar1;
  HANDLE pvVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_38 [8];
  LARGE_INTEGER local_30;
  undefined4 local_28;
  int local_24;
  DWORD local_20;
  undefined4 local_1c;
  void *local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850264;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = param_1;
  FUN_006c8ce0(param_1 + 0x38);
  local_8 = 0;
  FUN_006acaa0(param_2);
  if (*(int *)(local_14 + 0x30) == 0) {
    pvVar2 = CreateWaitableTimerA((LPSECURITY_ATTRIBUTES)0x0,0,(LPCSTR)0x0);
    *(HANDLE *)(local_14 + 0x30) = pvVar2;
    if (*(int *)(local_14 + 0x30) == 0) {
      local_20 = GetLastError();
      uVar3 = FUN_006abbb0(uVar1);
      FUN_00416430(local_20,uVar3);
      FUN_006aba00(local_38,"timer");
    }
    local_30.s.LowPart = 0xee1e5d00;
    local_30.s.HighPart = -1;
    local_30.QuadPart = (LONGLONG)__allmul(0xee1e5d00,0xffffffff,10,0);
    SetWaitableTimer(*(HANDLE *)(local_14 + 0x30),&local_30,300000,(PTIMERAPCROUTINE)0x0,(LPVOID)0x0
                     ,0);
  }
  iVar4 = get();
  if (iVar4 == 0) {
    local_24 = local_14;
    local_18 = operator_new(0xc);
    local_8._0_1_ = 1;
    if (local_18 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = FUN_006d8b00(local_24,0x10000);
    }
    local_28 = local_1c;
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_006c8eb0(local_1c);
  }
  local_8 = 0xffffffff;
  FUN_006c8d50();
  ExceptionList = local_10;
  return;
}


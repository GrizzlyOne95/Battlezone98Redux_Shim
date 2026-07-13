
void __fastcall FUN_006ad110(int param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  LARGE_INTEGER local_34;
  undefined1 local_2c [8];
  DWORD local_24;
  ulong local_20;
  int local_1c;
  LPOVERLAPPED local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850128;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  LOCK();
  *(undefined4 *)(param_1 + 0x24) = 1;
  UNLOCK();
  local_14 = param_1;
  iVar3 = get(uVar2);
  if (iVar3 != 0) {
    local_34.s.LowPart = 1;
    local_34.s.HighPart = 0;
    SetWaitableTimer(*(HANDLE *)(local_14 + 0x30),&local_34,1,(PTIMERAPCROUTINE)0x0,(LPVOID)0x0,0);
  }
  while( true ) {
    piVar4 = (int *)(local_14 + 0x18);
    LOCK();
    iVar3 = *piVar4;
    *piVar4 = *piVar4;
    UNLOCK();
    if (iVar3 < 1) break;
    FUN_006c8f00();
    local_8 = 0;
    FUN_006acc20(local_2c);
    FUN_006d8a70(local_14 + 0x54);
    cVar1 = FUN_004c85a0();
    if (cVar1 == '\0') {
      while (local_1c = get(), local_1c != 0) {
        FUN_006c8fb0();
        LOCK();
        *(int *)(local_14 + 0x18) = *(int *)(local_14 + 0x18) + -1;
        UNLOCK();
        FUN_006ac970();
      }
    }
    else {
      local_24 = 0;
      local_20 = 0;
      local_18 = (LPOVERLAPPED)0x0;
      GetQueuedCompletionStatus
                (*(HANDLE *)(local_14 + 0x14),&local_24,&local_20,&local_18,
                 *(DWORD *)(local_14 + 0x28));
      if (local_18 != (LPOVERLAPPED)0x0) {
        LOCK();
        *(int *)(local_14 + 0x18) = *(int *)(local_14 + 0x18) + -1;
        UNLOCK();
        FUN_006ac970();
      }
    }
    local_8 = 0xffffffff;
    FUN_006c8f30();
  }
  iVar3 = get(uVar2);
  if (iVar3 != 0) {
    get(uVar2);
    FUN_006ac600();
  }
  ExceptionList = local_10;
  return;
}


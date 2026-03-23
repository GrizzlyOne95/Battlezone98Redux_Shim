
void __fastcall FUN_006ad5e0(int param_1)

{
  int iVar1;
  BOOL BVar2;
  undefined4 uVar3;
  undefined1 local_14 [8];
  DWORD local_c;
  int local_8;
  
  LOCK();
  iVar1 = *(int *)(param_1 + 0x1c);
  *(int *)(param_1 + 0x1c) = 1;
  UNLOCK();
  if (iVar1 == 0) {
    LOCK();
    iVar1 = *(int *)(param_1 + 0x20);
    *(int *)(param_1 + 0x20) = 1;
    UNLOCK();
    if (iVar1 == 0) {
      local_8 = param_1;
      BVar2 = PostQueuedCompletionStatus(*(HANDLE *)(param_1 + 0x14),0,0,(LPOVERLAPPED)0x0);
      if (BVar2 == 0) {
        local_c = GetLastError();
        uVar3 = FUN_006abbb0();
        FUN_00416430(local_c,uVar3);
        FUN_006aba00(local_14,&DAT_008969a8);
      }
    }
  }
  return;
}


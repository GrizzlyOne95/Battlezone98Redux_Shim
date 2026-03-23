
void __thiscall FUN_006ad700(int param_1,undefined4 param_2)

{
  uint uVar1;
  LPOVERLAPPED lpOverlapped;
  BOOL BVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008501e8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  while (lpOverlapped = (LPOVERLAPPED)get(uVar1), lpOverlapped != (LPOVERLAPPED)0x0) {
    FUN_006c8fb0();
    lpOverlapped[1].u.s.Offset = 1;
    BVar2 = PostQueuedCompletionStatus(*(HANDLE *)(param_1 + 0x14),0,0,lpOverlapped);
    if (BVar2 == 0) {
      FUN_006c8ce0(param_1 + 0x38);
      local_8 = 0;
      FUN_006c9000(lpOverlapped);
      FUN_006d8a70(param_2);
      LOCK();
      *(undefined4 *)(param_1 + 0x34) = 1;
      UNLOCK();
      local_8 = 0xffffffff;
      FUN_006c8d50();
    }
  }
  ExceptionList = local_10;
  return;
}


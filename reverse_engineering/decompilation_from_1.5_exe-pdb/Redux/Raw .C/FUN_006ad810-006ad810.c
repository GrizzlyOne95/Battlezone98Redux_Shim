
void __thiscall FUN_006ad810(int param_1,LPOVERLAPPED param_2)

{
  uint uVar1;
  DWORD DVar2;
  BOOL BVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008501b8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  LOCK();
  DVar2 = param_2[1].u.s.Offset;
  if (DVar2 == 0) {
    param_2[1].u.s.Offset = 1;
    DVar2 = 0;
  }
  UNLOCK();
  if ((DVar2 == 1) &&
     (BVar3 = PostQueuedCompletionStatus(*(HANDLE *)(param_1 + 0x14),0,2,param_2), BVar3 == 0)) {
    FUN_006c8ce0(param_1 + 0x38);
    local_8 = 0;
    FUN_006c9000(param_2);
    LOCK();
    *(undefined4 *)(param_1 + 0x34) = 1;
    UNLOCK();
    local_8 = 0xffffffff;
    FUN_006c8d50(uVar1);
  }
  ExceptionList = local_10;
  return;
}


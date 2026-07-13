
void __thiscall FUN_006ad660(int param_1,LPOVERLAPPED param_2)

{
  uint uVar1;
  BOOL BVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008501b8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  param_2[1].u.s.Offset = 1;
  BVar2 = PostQueuedCompletionStatus(*(HANDLE *)(param_1 + 0x14),0,0,param_2);
  if (BVar2 == 0) {
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


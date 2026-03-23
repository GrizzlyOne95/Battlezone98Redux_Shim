
void __fastcall FUN_006ace60(int *param_1)

{
  int iVar1;
  DWORD DVar2;
  int *piVar3;
  
  while( true ) {
    piVar3 = (int *)(*param_1 + 0x24);
    LOCK();
    iVar1 = *piVar3;
    *piVar3 = *piVar3;
    UNLOCK();
    if (iVar1 != 0) break;
    DVar2 = WaitForSingleObject(*(HANDLE *)(*param_1 + 0x30),0xffffffff);
    if (DVar2 == 0) {
      LOCK();
      *(undefined4 *)(*param_1 + 0x34) = 1;
      UNLOCK();
      PostQueuedCompletionStatus(*(HANDLE *)(*param_1 + 0x14),0,1,(LPOVERLAPPED)0x0);
    }
  }
  return;
}


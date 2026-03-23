
void __fastcall FUN_006ac600(int param_1)

{
  char cVar1;
  HANDLE local_10;
  undefined4 local_c;
  int local_8;
  
  local_10 = *(HANDLE *)(param_1 + 8);
  local_c = *(undefined4 *)(param_1 + 4);
  local_8 = param_1;
  WaitForMultipleObjects(2,&local_10,0,0xffffffff);
  CloseHandle(*(HANDLE *)(local_8 + 8));
  cVar1 = FUN_006c8e10();
  if (cVar1 == '\0') {
    QueueUserAPC(FUN_006ac930,*(HANDLE *)(local_8 + 4),0);
    WaitForSingleObject(*(HANDLE *)(local_8 + 4),0xffffffff);
  }
  else {
    TerminateThread(*(HANDLE *)(local_8 + 4),0);
  }
  return;
}


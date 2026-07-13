
undefined4 FUN_006ac860(int *param_1)

{
  HANDLE hEvent;
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00850048;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  SetEvent((HANDLE)param_1[1]);
  (**(code **)(*param_1 + 4))(uVar1);
  hEvent = (HANDLE)param_1[2];
  if (param_1 != (int *)0x0) {
    (**(code **)*param_1)(1);
  }
  SetEvent(hEvent);
  SleepEx(0xffffffff,1);
  local_8 = 0xffffffff;
  FUN_006ac570();
  ExceptionList = local_10;
  return 0;
}


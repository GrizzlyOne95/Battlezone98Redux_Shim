
void __fastcall FUN_0043dc10(AudioInterface *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00845f39;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *(undefined ***)param_1 = DirectSound_AudioInterface::vftable;
  local_8 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x10));
  param_1[0x38] = (AudioInterface)0x0;
  MsgWaitForMultipleObjects(1,(HANDLE *)(param_1 + 0x2c),0,10,0);
  LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x10));
  while (param_1[0x39] == (AudioInterface)0x0) {
    PulseEvent(*(HANDLE *)(param_1 + 0x28));
    MsgWaitForMultipleObjects(1,(HANDLE *)(param_1 + 0x2c),0,10,0);
  }
  if (*(int *)(param_1 + 0x60) != 0) {
    (**(code **)(**(int **)(param_1 + 0x60) + 0x48))(*(undefined4 *)(param_1 + 0x60),uVar1);
    (**(code **)(**(int **)(param_1 + 0x60) + 8))(*(undefined4 *)(param_1 + 0x60));
  }
  CloseHandle(*(HANDLE *)(param_1 + 0x2c));
  CloseHandle(*(HANDLE *)(param_1 + 0x28));
  DeleteCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x10));
  FUN_00437a20();
  local_8 = 0xffffffff;
  theoraplayer::AudioInterface::~AudioInterface(param_1);
  ExceptionList = local_10;
  return;
}


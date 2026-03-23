
void FUN_006ac680(undefined4 *param_1,uint param_2)

{
  undefined4 uVar1;
  uintptr_t uVar2;
  undefined1 local_5c [8];
  undefined1 local_54 [8];
  undefined1 local_4c [8];
  DWORD local_44;
  undefined4 local_40;
  undefined4 *local_3c;
  uint local_38;
  DWORD local_34;
  undefined4 local_30;
  undefined4 *local_2c;
  DWORD local_28;
  undefined4 local_24;
  undefined4 *local_20;
  HANDLE local_1c;
  undefined4 *local_18;
  undefined4 *local_14;
  undefined4 *local_10;
  int local_c;
  HANDLE local_8;
  
  local_8 = (HANDLE)0x0;
  local_8 = CreateEventW((LPSECURITY_ATTRIBUTES)0x0,1,0,(LPCWSTR)0x0);
  param_1[1] = local_8;
  if (local_8 == (HANDLE)0x0) {
    local_28 = GetLastError();
    local_20 = param_1;
    local_10 = param_1;
    if (param_1 == (undefined4 *)0x0) {
      local_24 = 0;
    }
    else {
      local_24 = (**(code **)*param_1)(1);
    }
    uVar1 = FUN_006abbb0();
    FUN_00416430(local_28,uVar1);
    FUN_006aba00(local_4c,"thread.entry_event");
  }
  local_1c = CreateEventW((LPSECURITY_ATTRIBUTES)0x0,1,0,(LPCWSTR)0x0);
  *(HANDLE *)(local_c + 8) = local_1c;
  param_1[2] = local_1c;
  if (*(int *)(local_c + 8) == 0) {
    local_34 = GetLastError();
    local_2c = param_1;
    local_14 = param_1;
    if (param_1 == (undefined4 *)0x0) {
      local_30 = 0;
    }
    else {
      local_30 = (**(code **)*param_1)(1);
    }
    uVar1 = FUN_006abbb0();
    FUN_00416430(local_34,uVar1);
    FUN_006aba00(local_54,"thread.exit_event");
  }
  local_38 = 0;
  uVar2 = _beginthreadex((void *)0x0,param_2,FUN_006ac860,param_1,0,&local_38);
  *(uintptr_t *)(local_c + 4) = uVar2;
  if (*(int *)(local_c + 4) == 0) {
    local_44 = GetLastError();
    local_3c = param_1;
    local_18 = param_1;
    if (param_1 == (undefined4 *)0x0) {
      local_40 = 0;
    }
    else {
      local_40 = (**(code **)*param_1)(1);
    }
    if (local_8 != (HANDLE)0x0) {
      CloseHandle(local_8);
    }
    if (*(int *)(local_c + 8) != 0) {
      CloseHandle(*(HANDLE *)(local_c + 8));
    }
    uVar1 = FUN_006abbb0();
    FUN_00416430(local_44,uVar1);
    FUN_006aba00(local_5c,"thread");
  }
  if (local_8 != (HANDLE)0x0) {
    WaitForSingleObject(local_8,0xffffffff);
    CloseHandle(local_8);
  }
  return;
}



void __thiscall FUN_00435ef0(int param_1,char param_2)

{
  char cVar1;
  HMONITOR hMonitor;
  BOOL BVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uStack_c4;
  int local_a8;
  int local_a4;
  int local_a0;
  uint uStack_9c;
  int local_98;
  undefined1 local_91;
  int local_90;
  int local_8c;
  HWND local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  uint local_74;
  char local_6d;
  int local_6c;
  undefined1 local_68 [24];
  tagMONITORINFO local_50;
  tagRECT local_28;
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845b68;
  local_10 = ExceptionList;
  uStack_c4 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_c4;
  ExceptionList = &local_10;
  local_6c = param_1;
  local_18 = uStack_c4;
  cVar1 = (**(code **)(**(int **)(param_1 + 0xc) + 0x144))();
  if (cVar1 == '\0') {
    basic_string<>("WINDOW");
    local_8 = 0;
    (**(code **)(**(int **)(local_6c + 0xc) + 0x6c))(local_68,&local_88);
    local_8 = 0xffffffff;
    ~basic_string<>();
    hMonitor = MonitorFromWindow(local_88,2);
    local_50.cbSize = 0x28;
    local_8c = 0;
    local_90 = 0;
    local_84 = 0;
    local_78 = 0;
    local_7c = 0;
    local_80 = 0;
    BVar2 = GetMonitorInfoA(hMonitor,&local_50);
    if (BVar2 != 0) {
      local_84 = local_50.rcMonitor.right - local_50.rcMonitor.left;
      local_78 = local_50.rcMonitor.bottom - local_50.rcMonitor.top;
      GetWindowRect(local_88,&local_28);
      local_a0 = (**(code **)(**(int **)(local_6c + 0xc) + 0xc))();
      local_98 = (**(code **)(**(int **)(local_6c + 0xc) + 0x10))();
      local_7c = local_28.right - local_28.left;
      local_80 = local_28.bottom - local_28.top;
      local_8c = local_28.left;
      local_90 = local_28.top;
      local_6d = '\0';
      if (local_84 < local_7c) {
        local_7c = local_84;
        local_8c = local_50.rcMonitor.left;
        local_6d = '\x01';
      }
      else if ((((local_a0 != *(int *)(local_6c + 0x4c)) || (local_98 != *(int *)(local_6c + 0x50)))
               || (*(char *)(local_6c + 0x54) == '\0')) && (param_2 != '\0')) {
        local_8c = (local_84 - local_7c) / 2;
        local_6d = '\x01';
      }
      if (local_78 < local_80) {
        local_80 = local_78;
        local_90 = local_50.rcMonitor.top;
        local_6d = '\x01';
      }
      else if ((((local_a0 != *(int *)(local_6c + 0x4c)) || (local_98 != *(int *)(local_6c + 0x50)))
               || (*(char *)(local_6c + 0x54) == '\0')) && (param_2 != '\0')) {
        local_90 = (local_78 - local_80) / 2;
        local_6d = '\x01';
      }
      FUN_00665f60(&local_91,&local_a8,&local_a4);
      if ((local_a8 == local_84) && (local_a4 == local_78)) {
        local_80 = local_78;
        local_90 = local_50.rcMonitor.top;
        local_7c = local_84;
        local_8c = local_50.rcMonitor.left;
        local_6d = '\x01';
      }
      if (local_6d != '\0') {
        SetWindowPos(local_88,(HWND)0x0,local_8c,local_90,local_7c,local_80,0x24);
      }
    }
    uVar3 = GetWindowLongA(local_88,-0x10);
    local_74 = uVar3 & 0xfffaffff;
    if ((local_7c == local_84) && (local_80 == local_78)) {
      local_74 = uVar3 & 0xff3affff;
    }
    FUN_007d6a70("updateWindowStyle: screen %ld,%ld application %ld, %ld style=%lx\n",local_84,
                 local_78,local_7c,local_80,local_74);
    SetWindowLongA(local_88,-0x10,local_74);
    SetWindowPos(local_88,(HWND)0x0,0,0,0,0,0x27);
    (**(code **)(**(int **)(local_6c + 0xc) + 0x118))();
    local_8 = 1;
    (**(code **)(**(int **)(local_6c + 0xc) + 0x24))(1);
    FUN_004362a7();
    return;
  }
  cVar1 = (**(code **)(**(int **)(local_6c + 0xc) + 0x144))();
  uStack_9c = (uint)(cVar1 == '\0');
  *(bool *)(local_6c + 0x54) = cVar1 == '\0';
  uVar4 = (**(code **)(**(int **)(local_6c + 0xc) + 0x10))();
  *(undefined4 *)(local_6c + 0x50) = uVar4;
  uVar4 = (**(code **)(**(int **)(local_6c + 0xc) + 0xc))();
  *(undefined4 *)(local_6c + 0x4c) = uVar4;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}



void FUN_004363a0(uint *param_1,uint *param_2)

{
  uint uVar1;
  BOOL BVar2;
  HWND local_12c;
  HMONITOR local_128;
  int local_124;
  DWORD local_120;
  uint local_11c;
  uint local_118;
  char local_111;
  tagMONITORINFO local_110;
  CHAR local_e8 [32];
  undefined1 local_c8 [24];
  DEVMODEA local_b0;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845b9b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_110.cbSize = 0x48;
  local_14 = uVar1;
  basic_string<>("WINDOW");
  local_8 = 0;
  (**(code **)(**(int **)(local_124 + 0xc) + 0x6c))(local_c8,&local_12c,uVar1);
  local_8 = 0xffffffff;
  ~basic_string<>();
  local_128 = MonitorFromWindow(local_12c,2);
  BVar2 = GetMonitorInfoA(local_128,&local_110);
  if (BVar2 != 0) {
    local_111 = '\0';
    local_11c = 0;
    local_118 = 0;
    local_b0.dmDeviceName[0] = '\0';
    local_b0.dmDeviceName[1] = '\0';
    local_b0.dmDeviceName[2] = '\0';
    local_b0.dmDeviceName[3] = '\0';
    local_b0.dmDeviceName[4] = '\0';
    local_b0.dmDeviceName[5] = '\0';
    local_b0.dmDeviceName[6] = '\0';
    local_b0.dmDeviceName[7] = '\0';
    local_b0.dmDeviceName[8] = '\0';
    local_b0.dmDeviceName[9] = '\0';
    local_b0.dmDeviceName[10] = '\0';
    local_b0.dmDeviceName[0xb] = '\0';
    local_b0.dmDeviceName[0xc] = '\0';
    local_b0.dmDeviceName[0xd] = '\0';
    local_b0.dmDeviceName[0xe] = '\0';
    local_b0.dmDeviceName[0xf] = '\0';
    local_b0.dmDeviceName[0x10] = '\0';
    local_b0.dmDeviceName[0x11] = '\0';
    local_b0.dmDeviceName[0x12] = '\0';
    local_b0.dmDeviceName[0x13] = '\0';
    local_b0.dmDeviceName[0x14] = '\0';
    local_b0.dmDeviceName[0x15] = '\0';
    local_b0.dmDeviceName[0x16] = '\0';
    local_b0.dmDeviceName[0x17] = '\0';
    local_b0.dmDeviceName[0x18] = '\0';
    local_b0.dmDeviceName[0x19] = '\0';
    local_b0.dmDeviceName[0x1a] = '\0';
    local_b0.dmDeviceName[0x1b] = '\0';
    local_b0.dmDeviceName[0x1c] = '\0';
    local_b0.dmDeviceName[0x1d] = '\0';
    local_b0.dmDeviceName[0x1e] = '\0';
    local_b0.dmDeviceName[0x1f] = '\0';
    memset(&local_b0.dmSpecVersion,0,0x7c);
    local_b0.dmSize = 0x9c;
    local_120 = 0;
    while( true ) {
      BVar2 = EnumDisplaySettingsA(local_e8,local_120,&local_b0);
      if (BVar2 == 0) break;
      if ((*param_1 == local_b0.dmPelsWidth) && (*param_2 == local_b0.dmPelsHeight)) {
        local_111 = '\x01';
        break;
      }
      if (((local_11c < local_b0.dmPelsWidth) && (local_118 <= local_b0.dmPelsHeight)) ||
         ((local_11c <= local_b0.dmPelsWidth && (local_118 < local_b0.dmPelsHeight)))) {
        local_11c = local_b0.dmPelsWidth;
        local_118 = local_b0.dmPelsHeight;
      }
      local_120 = local_120 + 1;
    }
    if (((local_11c != 0) && (local_118 != 0)) && (local_111 == '\0')) {
      *param_1 = local_11c;
      *param_2 = local_118;
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}


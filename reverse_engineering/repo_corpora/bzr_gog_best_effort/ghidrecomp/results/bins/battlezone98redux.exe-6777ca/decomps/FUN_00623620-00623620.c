
void FUN_00623620(int param_1,undefined4 param_2,char *param_3,size_t param_4)

{
  DWORD dwMessageId;
  DWORD dwLanguageId;
  CHAR *lpBuffer;
  DWORD nSize;
  va_list *Arguments;
  DWORD local_11c;
  uint local_118;
  DWORD local_114;
  HKEY local_110;
  LSTATUS local_10c;
  CHAR local_108 [256];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  sprintf(&DAT_02a17370,
          "System\\CurrentControlSet\\Control\\MediaResources\\Joystick\\%s\\CurrentJoystickSettings"
          ,param_2);
  local_10c = RegOpenKeyExA((HKEY)0x80000002,&DAT_02a17370,0,1,&local_110);
  if (local_10c < 0) {
    Arguments = (va_list *)0x0;
    nSize = 0x100;
    lpBuffer = local_108;
    dwLanguageId = 0x400;
    dwMessageId = GetLastError();
    FormatMessageA(0x1000,(LPCVOID)0x0,dwMessageId,dwLanguageId,lpBuffer,nSize,Arguments);
    FUN_007d6830("Could not open registry joystick current config:\n%s",local_108);
  }
  else {
    sprintf(&DAT_02a17370,"Joystick%dOEMName",param_1 + 1);
    local_114 = 0x40;
    local_11c = 1;
    local_10c = RegQueryValueExA(local_110,&DAT_02a17370,(LPDWORD)0x0,&local_11c,&DAT_02a14470,
                                 &local_114);
    if (local_10c == 0) {
      RegCloseKey(local_110);
      sprintf(&DAT_02a17370,
              "System\\CurrentControlSet\\Control\\MediaProperties\\PrivateProperties\\Joystick\\OEM\\%s"
              ,&DAT_02a14470);
      local_10c = RegOpenKeyExA((HKEY)0x80000002,&DAT_02a17370,0,1,&local_110);
      if (local_10c == 0) {
        local_114 = 0x40;
        local_10c = RegQueryValueExA(local_110,"OEMName",(LPDWORD)0x0,&local_11c,&DAT_02a14470,
                                     &local_114);
        if (local_10c == 0) {
          strncpy(param_3,&DAT_02a14470,param_4);
        }
      }
    }
    RegCloseKey(local_110);
    local_118 = (uint)(local_10c == 0);
  }
  FUN_0083e885();
  return;
}


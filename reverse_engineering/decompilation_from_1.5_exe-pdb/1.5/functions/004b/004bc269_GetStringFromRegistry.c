/*
 * Entry: 004bc269
 * Name: GetStringFromRegistry
 * Namespace: Global
 * Signature: int GetStringFromRegistry(int param_1, char * param_2, char * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl GetStringFromRegistry(int param_1,char *param_2,char *param_3,int param_4)

{
  LSTATUS LVar1;
  DWORD dwMessageId;
  uint uVar2;
  DWORD dwLanguageId;
  CHAR *lpBuffer;
  DWORD nSize;
  va_list *Arguments;
  DWORD local_118 [3];
  HKEY local_10c;
  CHAR local_108 [108];
  undefined1 local_9c [148];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_9c;
  sprintf(registryKeyString,
          "System\\CurrentControlSet\\Control\\MediaResources\\Joystick\\%s\\CurrentJoystickSettings"
          ,param_2);
  LVar1 = RegOpenKeyExA((HKEY)0x80000002,registryKeyString,0,1,&local_10c);
  if (LVar1 < 0) {
    Arguments = (va_list *)0x0;
    nSize = 0x100;
    lpBuffer = local_108;
    dwLanguageId = 0x400;
    dwMessageId = GetLastError();
    FormatMessageA(0x1000,(LPCVOID)0x0,dwMessageId,dwLanguageId,lpBuffer,nSize,Arguments);
    DEBUG_systemWarning("Could not open registry joystick current config:\n%s");
    uVar2 = 0;
  }
  else {
    sprintf(registryKeyString,"Joystick%dOEMName",param_1 + 1);
    local_118[0] = 1;
    local_118[1] = 0x40;
    local_118[2] = RegQueryValueExA(local_10c,registryKeyString,(LPDWORD)0x0,local_118,
                                    (LPBYTE)registryString,local_118 + 1);
    if (local_118[2] == 0) {
      RegCloseKey(local_10c);
      sprintf(registryKeyString,
              "System\\CurrentControlSet\\Control\\MediaProperties\\PrivateProperties\\Joystick\\OEM\\%s"
              ,registryString);
      local_118[2] = RegOpenKeyExA((HKEY)0x80000002,registryKeyString,0,1,&local_10c);
      if (local_118[2] == 0) {
        local_118[1] = 0x40;
        local_118[2] = RegQueryValueExA(local_10c,"OEMName",(LPDWORD)0x0,local_118,
                                        (LPBYTE)registryString,local_118 + 1);
        if (local_118[2] == 0) {
          strncpy(param_3,registryString,param_4);
        }
      }
    }
    RegCloseKey(local_10c);
    uVar2 = (uint)(local_118[2] == 0);
  }
  return uVar2;
}

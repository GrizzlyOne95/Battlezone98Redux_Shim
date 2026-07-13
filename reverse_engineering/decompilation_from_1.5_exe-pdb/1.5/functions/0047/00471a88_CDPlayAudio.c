/*
 * Entry: 00471a88
 * Name: CDPlayAudio
 * Namespace: Global
 * Signature: int CDPlayAudio(ulong param_1, ulong param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CDPlayAudio(ulong param_1,ulong param_2)

{
  MCIERROR MVar1;
  DWORD_PTR dwParam1;
  undefined1 local_10 [4];
  ulong local_c;
  ulong local_8;
  
  local_c = param_1;
  dwParam1 = 4;
  if (param_2 != 0) {
    dwParam1 = 0xc;
    local_8 = param_2;
  }
  MVar1 = mciSendCommandA(CD_DeviceID,0x806,dwParam1,(DWORD_PTR)local_10);
  return MVar1;
}

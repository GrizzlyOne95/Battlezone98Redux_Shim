/*
 * Entry: 00471bec
 * Name: VerifyCDTrackLength
 * Namespace: Global
 * Signature: int VerifyCDTrackLength(ulong param_1, ulong param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl VerifyCDTrackLength(ulong param_1,ulong param_2)

{
  MCIERROR MVar1;
  undefined4 local_14;
  ulong local_10;
  undefined4 local_c;
  ulong local_8;
  
  if (CD_OK != 0) {
    local_14 = 0;
    local_10 = 0;
    local_8 = param_1;
    local_c = 1;
    MVar1 = mciSendCommandA(CD_DeviceID,0x814,0x110,(DWORD_PTR)&local_14);
    if ((MVar1 == 0) && (local_10 == param_2)) {
      return 1;
    }
  }
  return 0;
}

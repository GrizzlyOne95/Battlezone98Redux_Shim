/*
 * Entry: 00471d01
 * Name: PlayerState
 * Namespace: Global
 * Signature: int PlayerState(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl PlayerState(void)

{
  MCIERROR MVar1;
  undefined1 local_14 [4];
  int local_10;
  undefined4 local_c;
  
  if (CD_OK != 0) {
    local_c = 4;
    MVar1 = mciSendCommandA(CD_DeviceID,0x814,0x100,(DWORD_PTR)local_14);
    if (MVar1 == 0) {
      if (local_10 == 0x20d) {
        return 2;
      }
      if (local_10 == 0x20e) {
        return 3;
      }
      if (local_10 == 0x211) {
        return 4;
      }
      if (local_10 == 0x212) {
        return 1;
      }
    }
    else {
      PlayerDone();
    }
  }
  return 5;
}

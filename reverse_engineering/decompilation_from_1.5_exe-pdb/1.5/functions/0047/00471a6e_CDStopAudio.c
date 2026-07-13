/*
 * Entry: 00471a6e
 * Name: CDStopAudio
 * Namespace: Global
 * Signature: int CDStopAudio(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CDStopAudio(void)

{
  MCIERROR MVar1;
  undefined1 local_4 [4];
  
  MVar1 = mciSendCommandA(CD_DeviceID,0x808,0,(DWORD_PTR)local_4);
  return MVar1;
}

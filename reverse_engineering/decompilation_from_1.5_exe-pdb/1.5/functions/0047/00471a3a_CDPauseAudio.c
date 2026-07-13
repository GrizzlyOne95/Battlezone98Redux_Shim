/*
 * Entry: 00471a3a
 * Name: CDPauseAudio
 * Namespace: Global
 * Signature: int CDPauseAudio(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CDPauseAudio(void)

{
  MCIERROR MVar1;
  undefined1 local_4 [4];
  
  MVar1 = mciSendCommandA(CD_DeviceID,0x809,0,(DWORD_PTR)local_4);
  return MVar1;
}

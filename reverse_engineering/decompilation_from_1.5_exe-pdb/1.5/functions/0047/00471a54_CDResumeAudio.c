/*
 * Entry: 00471a54
 * Name: CDResumeAudio
 * Namespace: Global
 * Signature: int CDResumeAudio(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CDResumeAudio(void)

{
  MCIERROR MVar1;
  undefined1 local_4 [4];
  
  MVar1 = mciSendCommandA(CD_DeviceID,0x855,0,(DWORD_PTR)local_4);
  return MVar1;
}

/*
 * Entry: 00471a17
 * Name: CDDone
 * Namespace: Global
 * Signature: int CDDone(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CDDone(void)

{
  undefined1 local_4 [4];
  
  mciSendCommandA(CD_DeviceID,0x804,0,(DWORD_PTR)local_4);
  CD_DeviceID = -1;
  return 0;
}

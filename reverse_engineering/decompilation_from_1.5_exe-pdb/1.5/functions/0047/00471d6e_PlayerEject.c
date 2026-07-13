/*
 * Entry: 00471d6e
 * Name: PlayerEject
 * Namespace: Global
 * Signature: void PlayerEject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PlayerEject(void)

{
  MCIERROR MVar1;
  undefined1 local_c [12];
  
  MVar1 = mciSendCommandA(CD_DeviceID,0x80d,0x100,(DWORD_PTR)local_c);
  if (MVar1 != 0) {
    PlayerDone();
  }
  return;
}

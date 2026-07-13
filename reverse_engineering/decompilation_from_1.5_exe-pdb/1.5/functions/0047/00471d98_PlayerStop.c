/*
 * Entry: 00471d98
 * Name: PlayerStop
 * Namespace: Global
 * Signature: void PlayerStop(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PlayerStop(void)

{
  int iVar1;
  
  if (CD_OK != 0) {
    do {
      CDStopAudio();
      iVar1 = PlayerState();
    } while (iVar1 != 2);
  }
  return;
}

/*
 * Entry: 00471ceb
 * Name: PlayerDone
 * Namespace: Global
 * Signature: void PlayerDone(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PlayerDone(void)

{
  if (CD_OK != 0) {
    CDDone();
    CD_OK = 0;
  }
  return;
}

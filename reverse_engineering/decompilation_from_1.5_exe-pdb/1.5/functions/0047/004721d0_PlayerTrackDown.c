/*
 * Entry: 004721d0
 * Name: PlayerTrackDown
 * Namespace: Global
 * Signature: void PlayerTrackDown(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PlayerTrackDown(void)

{
  int unaff_EDI;
  
  if (CD_OK != 0) {
    pMoveTrack((Disc *)0xffffffff,unaff_EDI);
  }
  return;
}

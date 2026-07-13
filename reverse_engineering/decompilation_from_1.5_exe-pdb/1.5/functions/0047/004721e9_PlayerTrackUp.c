/*
 * Entry: 004721e9
 * Name: PlayerTrackUp
 * Namespace: Global
 * Signature: void PlayerTrackUp(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PlayerTrackUp(void)

{
  int unaff_EDI;
  
  if (CD_OK != 0) {
    pMoveTrack((Disc *)0x1,unaff_EDI);
  }
  return;
}

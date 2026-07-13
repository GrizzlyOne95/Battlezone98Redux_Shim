/*
 * Entry: 00471b3d
 * Name: CDTrackExists
 * Namespace: Global
 * Signature: int CDTrackExists(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CDTrackExists(int param_1)

{
  if ((ThisDisc.LowestTrack <= param_1) && (param_1 <= ThisDisc.HighestTrack)) {
    return 1;
  }
  return 0;
}

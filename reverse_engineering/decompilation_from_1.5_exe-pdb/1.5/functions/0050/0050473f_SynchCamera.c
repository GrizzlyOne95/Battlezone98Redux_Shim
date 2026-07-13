/*
 * Entry: 0050473f
 * Name: SynchCamera
 * Namespace: Global
 * Signature: void SynchCamera(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SynchCamera(void)

{
  InformMouseOfVideoModeChange();
  Init_View_Record(0);
  return;
}

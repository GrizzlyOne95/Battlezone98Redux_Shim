/*
 * Entry: 004c179a
 * Name: toggle_show_hardpoints
 * Namespace: Global
 * Signature: void toggle_show_hardpoints(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl toggle_show_hardpoints(void)

{
  HardPoints::Toggle(&hardPoints);
  return;
}

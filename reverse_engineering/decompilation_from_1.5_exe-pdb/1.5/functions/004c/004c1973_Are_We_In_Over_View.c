/*
 * Entry: 004c1973
 * Name: Are_We_In_Over_View
 * Namespace: Global
 * Signature: int Are_We_In_Over_View(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Are_We_In_Over_View(void)

{
  return (uint)(View_Record.Current_View == OVER_VIEW);
}

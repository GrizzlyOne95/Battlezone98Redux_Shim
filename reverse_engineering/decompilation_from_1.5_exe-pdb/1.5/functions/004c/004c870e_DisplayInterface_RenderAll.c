/*
 * Entry: 004c870e
 * Name: DisplayInterface_RenderAll
 * Namespace: Global
 * Signature: void DisplayInterface_RenderAll(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DisplayInterface_RenderAll(void)

{
  DisplayInterface::RenderAll(View_Record.Current_View);
  return;
}

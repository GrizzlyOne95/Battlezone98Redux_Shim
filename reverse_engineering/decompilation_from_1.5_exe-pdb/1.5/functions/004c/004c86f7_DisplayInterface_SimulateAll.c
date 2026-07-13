/*
 * Entry: 004c86f7
 * Name: DisplayInterface_SimulateAll
 * Namespace: Global
 * Signature: void DisplayInterface_SimulateAll(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DisplayInterface_SimulateAll(void)

{
  float fVar1;
  
  fVar1 = TimeStepLocal();
  DisplayInterface::SimulateAll(View_Record.Current_View,fVar1);
  return;
}

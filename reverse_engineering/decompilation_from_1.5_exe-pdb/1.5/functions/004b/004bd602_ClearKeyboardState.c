/*
 * Entry: 004bd602
 * Name: ClearKeyboardState
 * Namespace: Global
 * Signature: void ClearKeyboardState(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ClearKeyboardState(void)

{
  discreteClrMap[0] = 0;
  discreteClrMap[1] = 0;
  discreteClrMap[2] = 0;
  discreteClrMap[3] = 0;
  discreteSetMap[0] = 0;
  discreteSetMap[1] = 0;
  discreteSetMap[2] = 0;
  discreteSetMap[3] = 0;
  return;
}

/*
 * Entry: 004b9ee8
 * Name: ProcessInput
 * Namespace: Global
 * Signature: void ProcessInput(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ProcessInput(void)

{
  short sVar1;
  ushort uVar2;
  
  sVar1 = user_controls.key;
  if (inputCalled != 0) {
    inputCalled = 0;
    return;
  }
  test_cheat_codes(user_controls.key);
  uVar2 = MapKeyInput(sVar1);
  if (uVar2 != 0) {
    ProcessGK((uint)uVar2);
  }
  inputFound = 0;
  return;
}

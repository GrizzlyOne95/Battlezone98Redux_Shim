/*
 * Entry: 004cf887
 * Name: InfoDisplay::Cleanup
 * Namespace: InfoDisplay
 * Signature: void Cleanup(InfoDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall InfoDisplay::Cleanup(InfoDisplay *this)

{
  int iVar1;
  
  ClearObjectives(this);
  iVar1 = IsJapanese();
  if (iVar1 != 0) {
    operator_delete__(charMap);
    charMap = (short *)0x0;
    charCount = 0;
  }
  return;
}

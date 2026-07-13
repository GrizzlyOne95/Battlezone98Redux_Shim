/*
 * Entry: 004cf293
 * Name: InfoDisplay::CurrentInfoDisplay
 * Namespace: InfoDisplay
 * Signature: GameObject * CurrentInfoDisplay(InfoDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall InfoDisplay::CurrentInfoDisplay(InfoDisplay *this)

{
  if ((this->objectShow == false) && ((UserProfilePtr->playOption & 0x80) == 0)) {
    return (GameObject *)0x0;
  }
  return this->objectSave;
}

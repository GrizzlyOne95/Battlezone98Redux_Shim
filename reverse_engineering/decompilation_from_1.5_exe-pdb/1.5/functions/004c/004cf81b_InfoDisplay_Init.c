/*
 * Entry: 004cf81b
 * Name: InfoDisplay::Init
 * Namespace: InfoDisplay
 * Signature: void Init(InfoDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall InfoDisplay::Init(InfoDisplay *this)

{
  WIDTH = GetINIInt("Config","InfoWidth",0xb4,"lang.ini");
  HEIGHT = GetINIInt("Config","InfoHeight",100,"lang.ini");
  RIGHT_OFFSET = GetINIInt("Config","InfoRightOffset",0x14,"lang.ini");
  this->objectiveLast = 0.0;
  this->objectSave = (GameObject *)0x0;
  this->objectShow = false;
  InitJChar();
  return;
}

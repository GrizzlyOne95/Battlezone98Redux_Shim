/*
 * Entry: 004c166a
 * Name: SelectionDisplay::PostLoad
 * Namespace: SelectionDisplay
 * Signature: void PostLoad(SelectionDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SelectionDisplay::PostLoad(SelectionDisplay *this)

{
  memset(this->colorMap,0,0x400);
  this->colorMap[DisplayInterface::colorGreen] = 1;
  this->colorMap[DisplayInterface::colorDkGreen] = 1;
  this->colorMap[DisplayInterface::colorYellow] = 2;
  this->colorMap[DisplayInterface::colorDkYellow] = 2;
  this->colorMap[DisplayInterface::colorRed] = 3;
  this->colorMap[DisplayInterface::colorDkRed] = 3;
  this->colorMap[DisplayInterface::colorBlue] = 4;
  this->colorMap[DisplayInterface::colorDkBlue] = 4;
  return;
}

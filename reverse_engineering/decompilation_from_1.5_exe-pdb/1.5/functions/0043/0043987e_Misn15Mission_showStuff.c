/*
 * Entry: 0043987e
 * Name: Misn15Mission::showStuff
 * Namespace: Misn15Mission
 * Signature: void showStuff(Misn15Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn15Mission::showStuff(Misn15Mission *this)

{
  long lVar1;
  
  InfoDisplay::ClearObjectives(&infoDisplay);
  lVar1 = DisplayInterface::colorWhite;
  if ((this->field16_0x40)._s_0.cca_here != false) {
    lVar1 = DisplayInterface::colorGreen;
  }
  InfoDisplay::AddObjective(&infoDisplay,"misn1501.otf",lVar1,8.0);
  lVar1 = DisplayInterface::colorWhite;
  if ((this->field16_0x40)._s_0.found_group1 != false) {
    lVar1 = DisplayInterface::colorGreen;
  }
  InfoDisplay::AddObjective(&infoDisplay,"misn1502.otf",lVar1,8.0);
  lVar1 = DisplayInterface::colorWhite;
  if ((this->field16_0x40)._s_0.silo_built != false) {
    lVar1 = DisplayInterface::colorGreen;
  }
  InfoDisplay::AddObjective(&infoDisplay,"misn1503.otf",lVar1,8.0);
  lVar1 = DisplayInterface::colorWhite;
  if ((this->field16_0x40)._s_0.won != false) {
    lVar1 = DisplayInterface::colorGreen;
  }
  InfoDisplay::AddObjective(&infoDisplay,"misn1504.otf",lVar1,8.0);
  return;
}

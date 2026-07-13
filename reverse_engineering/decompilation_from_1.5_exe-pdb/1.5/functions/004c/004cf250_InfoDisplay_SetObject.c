/*
 * Entry: 004cf250
 * Name: InfoDisplay::SetObject
 * Namespace: InfoDisplay
 * Signature: void SetObject(InfoDisplay * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall InfoDisplay::SetObject(InfoDisplay *this,GameObject *param_1)

{
  int iVar1;
  
  if (param_1 == (GameObject *)0x0) {
    this->objectShow = false;
  }
  if ((param_1 != this->objectSave) && (this->objectSave = param_1, param_1 != (GameObject *)0x0)) {
    iVar1 = (**(code **)param_1->_padding_)();
    (this->objectMessage).text = *(char **)(iVar1 + 0x14c);
  }
  (this->objectMessage).color = DisplayInterface::colorWhite;
  return;
}

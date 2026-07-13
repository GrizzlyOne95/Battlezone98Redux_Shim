/*
 * Entry: 004c4907
 * Name: ControlPanel::AltCommand
 * Namespace: ControlPanel
 * Signature: void AltCommand(ControlPanel * this, AiCommand param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ControlPanel::AltCommand(ControlPanel *this,AiCommand param_1,GameObject *param_2)

{
  VECTOR_3D *pVVar1;
  
  FillCmdButton(this,&this->altButton,param_1,param_2);
  if (param_2 == (GameObject *)0x0) {
    (this->altButton).pos = (VECTOR_3D *)0x0;
  }
  else {
    pVVar1 = (VECTOR_3D *)(**(code **)(param_2->_padding_ + 0xc))();
    (this->altButton).pos = pVVar1;
  }
  return;
}

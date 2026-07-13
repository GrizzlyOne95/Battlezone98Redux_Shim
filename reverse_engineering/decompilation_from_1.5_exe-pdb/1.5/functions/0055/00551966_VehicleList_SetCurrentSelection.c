/*
 * Entry: 00551966
 * Name: VehicleList::SetCurrentSelection
 * Namespace: VehicleList
 * Signature: void SetCurrentSelection(VehicleList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall VehicleList::SetCurrentSelection(VehicleList *this)

{
  char cVar1;
  TextLabel *this_00;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  
  this_00 = this->vehicleNameLabel;
  if (this_00 != (TextLabel *)0x0) {
    if (((this->s == (_s *)0x0) || (iVar2 = this->currentSelection, iVar2 < 0)) ||
       (this->count <= iVar2)) {
      TextLabel::SetLabelText(this_00,"");
    }
    else {
      TextLabel::SetLabelText(this_00,this->s[iVar2].label);
      TextLabel::DrawLabelText(this->vehicleNameLabel,(char *)0x0,0);
      pcVar3 = this->s[this->currentSelection].name;
      pcVar4 = net_defaults.playercraft;
      do {
        cVar1 = *pcVar3;
        pcVar3 = pcVar3 + 1;
        *pcVar4 = cVar1;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
      SetPlayerBlob(Net::dp,Net::myPlayerID,net_defaults.playercraft,Net::Team);
    }
    TextLabel::DrawLabelText(this->vehicleNameLabel,(char *)0x0,0);
  }
  if (this->vehicleDesc != (TextWindow *)0x0) {
    if (((this->s == (_s *)0x0) || (iVar2 = this->currentSelection, iVar2 < 0)) ||
       (this->count <= iVar2)) {
      pcVar3 = "";
    }
    else {
      pcVar3 = this->s[iVar2].description;
    }
    TextWindow::SetWindowTextA(this->vehicleDesc,pcVar3);
    (**(code **)(this->vehicleDesc->_padding_ + 4))(0);
  }
  return;
}

/*
 * Entry: 005516ae
 * Name: VehicleList::MoveForward
 * Namespace: VehicleList
 * Signature: void MoveForward(VehicleList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall VehicleList::MoveForward(VehicleList *this)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  
  iVar1 = this->currentSelection;
  iVar2 = iVar1;
  while( true ) {
    if (this->validVehicles == (char *)0x0) {
      return;
    }
    pcVar3 = strstr(this->validVehicles,this->s[iVar2].name);
    if (pcVar3 != (char *)0x0) break;
    this->currentSelection = this->currentSelection + 1;
    if (this->count <= this->currentSelection) {
      this->currentSelection = 0;
    }
    iVar2 = this->currentSelection;
    if (iVar2 == iVar1) {
      return;
    }
  }
  return;
}

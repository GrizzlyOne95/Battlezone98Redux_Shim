/*
 * Entry: 005516ed
 * Name: VehicleList::MoveBackward
 * Namespace: VehicleList
 * Signature: void MoveBackward(VehicleList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall VehicleList::MoveBackward(VehicleList *this)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  
  iVar2 = this->currentSelection;
  iVar3 = iVar2;
  while( true ) {
    if (this->validVehicles == (char *)0x0) {
      return;
    }
    pcVar4 = strstr(this->validVehicles,this->s[iVar3].name);
    if (pcVar4 != (char *)0x0) break;
    piVar1 = &this->currentSelection;
    *piVar1 = *piVar1 + -1;
    if (*piVar1 < 0) {
      this->currentSelection = this->count + -1;
    }
    iVar3 = this->currentSelection;
    if (iVar3 == iVar2) {
      return;
    }
  }
  return;
}

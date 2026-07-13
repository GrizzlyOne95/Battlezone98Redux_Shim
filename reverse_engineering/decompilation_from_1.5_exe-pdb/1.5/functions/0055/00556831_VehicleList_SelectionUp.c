/*
 * Entry: 00556831
 * Name: VehicleList::SelectionUp
 * Namespace: VehicleList
 * Signature: void SelectionUp(VehicleList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall VehicleList::SelectionUp(VehicleList *this)

{
  int iVar1;
  
  iVar1 = this->currentSelection;
  if (iVar1 < 1) {
    iVar1 = this->count;
  }
  this->currentSelection = iVar1 + -1;
  MoveBackward(this);
  SetCurrentSelection(this);
  return;
}

/*
 * Entry: 0055680a
 * Name: VehicleList::SelectionDown
 * Namespace: VehicleList
 * Signature: void SelectionDown(VehicleList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall VehicleList::SelectionDown(VehicleList *this)

{
  if (this->currentSelection < this->count + -1) {
    this->currentSelection = this->currentSelection + 1;
  }
  else {
    this->currentSelection = 0;
  }
  MoveForward(this);
  SetCurrentSelection(this);
  return;
}

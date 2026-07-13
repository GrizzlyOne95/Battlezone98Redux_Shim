/*
 * Entry: 005566d9
 * Name: VehicleList::Init
 * Namespace: VehicleList
 * Signature: void Init(VehicleList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall VehicleList::Init(VehicleList *this)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  if (this->count != 0) {
    iVar2 = 0;
    if (0 < this->count) {
      do {
        free(*(void **)((int)&this->s->name + iVar1));
        free(*(void **)((int)&this->s->description + iVar1));
        free(*(void **)((int)&this->s->label + iVar1));
        free(*(void **)((int)&this->s->avi + iVar1));
        iVar2 = iVar2 + 1;
        iVar1 = iVar1 + 0x10;
      } while (iVar2 < this->count);
    }
    free(this->s);
  }
  this->currentSelection = 0;
  this->count = 0;
  this->s = (_s *)0x0;
  free(this->validVehicles);
  this->validVehicles = (char *)0x0;
  validVehicles = (char *)0x0;
  SetCurrentSelection(this);
  return;
}

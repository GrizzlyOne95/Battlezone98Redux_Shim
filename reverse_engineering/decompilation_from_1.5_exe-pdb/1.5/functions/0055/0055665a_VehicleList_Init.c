/*
 * Entry: 0055665a
 * Name: VehicleList::Init
 * Namespace: VehicleList
 * Signature: void Init(VehicleList * this, TextLabel * param_1, TextWindow * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall VehicleList::Init(VehicleList *this,TextLabel *param_1,TextWindow *param_2)

{
  int iVar1;
  int iVar2;
  
  this->vehicleNameLabel = param_1;
  this->vehicleDesc = param_2;
  iVar2 = 0;
  if (this->count != 0) {
    iVar1 = 0;
    if (0 < this->count) {
      do {
        free(*(void **)((int)&this->s->name + iVar2));
        free(*(void **)((int)&this->s->description + iVar2));
        free(*(void **)((int)&this->s->label + iVar2));
        free(*(void **)((int)&this->s->avi + iVar2));
        iVar1 = iVar1 + 1;
        iVar2 = iVar2 + 0x10;
      } while (iVar1 < this->count);
    }
    free(this->s);
  }
  this->currentSelection = 0;
  this->count = 0;
  this->s = (_s *)0x0;
  this->validVehicles = (char *)0x0;
  validVehicles = (char *)0x0;
  SetCurrentSelection(this);
  return;
}

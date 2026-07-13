/*
 * Entry: 00551a82
 * Name: SimpleVehicleList::~SimpleVehicleList
 * Namespace: SimpleVehicleList
 * Signature: void ~SimpleVehicleList(SimpleVehicleList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SimpleVehicleList::~SimpleVehicleList(SimpleVehicleList *this)

{
  int iVar1;
  
  if (this->count != 0) {
    iVar1 = 0;
    if (0 < this->count) {
      do {
        free(this->s[iVar1].name);
        free(this->s[iVar1].label);
        iVar1 = iVar1 + 1;
      } while (iVar1 < this->count);
    }
    free(this->s);
  }
  this->count = 0;
  this->s = (_s *)0x0;
  return;
}

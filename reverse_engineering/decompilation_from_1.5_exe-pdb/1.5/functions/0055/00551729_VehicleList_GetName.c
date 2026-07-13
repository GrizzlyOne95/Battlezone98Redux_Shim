/*
 * Entry: 00551729
 * Name: VehicleList::GetName
 * Namespace: VehicleList
 * Signature: char * GetName(VehicleList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __thiscall VehicleList::GetName(VehicleList *this)

{
  int iVar1;
  
  iVar1 = this->currentSelection;
  if ((-1 < iVar1) && (iVar1 < this->count)) {
    return this->s[iVar1].name;
  }
  return (char *)0x0;
}

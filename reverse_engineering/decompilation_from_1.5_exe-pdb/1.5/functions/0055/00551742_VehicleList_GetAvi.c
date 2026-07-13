/*
 * Entry: 00551742
 * Name: VehicleList::GetAvi
 * Namespace: VehicleList
 * Signature: char * GetAvi(VehicleList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __thiscall VehicleList::GetAvi(VehicleList *this)

{
  int iVar1;
  undefined1 local_30 [48];
  
  iVar1 = this->currentSelection;
  if (((-1 < iVar1) && (iVar1 < this->count)) &&
     (iVar1 = stat64i32(this->s[iVar1].avi,local_30), iVar1 == 0)) {
    return this->s[this->currentSelection].avi;
  }
  return (char *)0x0;
}

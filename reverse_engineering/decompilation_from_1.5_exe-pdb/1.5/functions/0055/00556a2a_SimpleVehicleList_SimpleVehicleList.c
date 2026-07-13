/*
 * Entry: 00556a2a
 * Name: SimpleVehicleList::SimpleVehicleList
 * Namespace: SimpleVehicleList
 * Signature: SimpleVehicleList * SimpleVehicleList(SimpleVehicleList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SimpleVehicleList * __thiscall SimpleVehicleList::SimpleVehicleList(SimpleVehicleList *this)

{
  int iVar1;
  char *pcVar2;
  
  this->s = (_s *)0x0;
  this->count = 0;
  if (Net::bNations != false) {
    iVar1 = ItemExists("netveh1.odf");
    if (iVar1 != 0) {
      pcVar2 = "netveh1.odf";
      goto LAB_00556a55;
    }
  }
  pcVar2 = "netveh.odf";
LAB_00556a55:
  Load(this,pcVar2);
  return this;
}

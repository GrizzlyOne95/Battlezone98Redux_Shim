/*
 * Entry: 004524b0
 * Name: PathZone::PathZone
 * Namespace: PathZone
 * Signature: PathZone * PathZone(PathZone * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PathZone * __thiscall PathZone::PathZone(PathZone *this)

{
  vector<Strip_*,std::allocator<Strip_*>_> *pvVar1;
  int *piVar2;
  
  pvVar1 = &this->terrainStrips;
  piVar2 = operator_new(4);
  if (piVar2 != (int *)0x0) {
    *piVar2 = (int)pvVar1;
    pvVar1->_padding_ = (int)piVar2;
    (this->terrainStrips)._Myfirst = (Strip **)0x0;
    (this->terrainStrips)._Mylast = (Strip **)0x0;
    (this->terrainStrips)._Myend = (Strip **)0x0;
    return this;
  }
  pvVar1->_padding_ = 0;
  (this->terrainStrips)._Myfirst = (Strip **)0x0;
  (this->terrainStrips)._Mylast = (Strip **)0x0;
  (this->terrainStrips)._Myend = (Strip **)0x0;
  return this;
}

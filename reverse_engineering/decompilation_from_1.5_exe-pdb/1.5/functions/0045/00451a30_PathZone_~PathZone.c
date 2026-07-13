/*
 * Entry: 00451a30
 * Name: PathZone::~PathZone
 * Namespace: PathZone
 * Signature: void ~PathZone(PathZone * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathZone::~PathZone(PathZone *this)

{
  Strip **ppSVar1;
  
  ppSVar1 = (this->terrainStrips)._Myfirst;
  if (ppSVar1 != (Strip **)0x0) {
    operator_delete(ppSVar1);
  }
  (this->terrainStrips)._Myfirst = (Strip **)0x0;
  (this->terrainStrips)._Mylast = (Strip **)0x0;
  (this->terrainStrips)._Myend = (Strip **)0x0;
  operator_delete((void *)(this->terrainStrips)._padding_);
  return;
}

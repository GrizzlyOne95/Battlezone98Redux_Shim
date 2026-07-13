/*
 * Entry: 004afb2c
 * Name: ScrapFieldFeature::PreLoad
 * Namespace: ScrapFieldFeature
 * Signature: void PreLoad(ScrapFieldFeature * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScrapFieldFeature::PreLoad(ScrapFieldFeature *this)

{
  GameObjectClass *pGVar1;
  
  pGVar1 = GameObjectClass::Find(0x31726373706e);
  this->objClass[0] = pGVar1;
  pGVar1 = GameObjectClass::Find(0x32726373706e);
  this->objClass[1] = pGVar1;
  pGVar1 = GameObjectClass::Find(0x33726373706e);
  this->objClass[2] = pGVar1;
  return;
}

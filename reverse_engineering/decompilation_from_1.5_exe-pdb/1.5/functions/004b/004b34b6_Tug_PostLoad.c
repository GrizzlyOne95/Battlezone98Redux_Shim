/*
 * Entry: 004b34b6
 * Name: Tug::PostLoad
 * Namespace: Tug
 * Signature: bool PostLoad(Tug * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Tug::PostLoad(Tug *this)

{
  bool bVar1;
  
  if (this->cargo != (GameObject *)0x0) {
    SetCargo(this,this->cargo);
  }
  bVar1 = Craft::PostLoad((Craft *)this);
  return bVar1;
}

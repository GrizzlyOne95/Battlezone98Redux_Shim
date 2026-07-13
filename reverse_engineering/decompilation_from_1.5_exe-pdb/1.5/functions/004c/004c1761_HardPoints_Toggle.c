/*
 * Entry: 004c1761
 * Name: HardPoints::Toggle
 * Namespace: HardPoints
 * Signature: void Toggle(HardPoints * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall HardPoints::Toggle(HardPoints *this)

{
  bool bVar1;
  
  bVar1 = this->showHardpoints == false;
  this->showHardpoints = bVar1;
  if (bVar1) {
    Show(this);
    return;
  }
  Hide(this);
  return;
}

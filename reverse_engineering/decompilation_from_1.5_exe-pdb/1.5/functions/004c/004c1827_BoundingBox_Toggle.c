/*
 * Entry: 004c1827
 * Name: BoundingBox::Toggle
 * Namespace: BoundingBox
 * Signature: void Toggle(BoundingBox * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BoundingBox::Toggle(BoundingBox *this)

{
  bool bVar1;
  
  bVar1 = this->showCollision == false;
  this->showCollision = bVar1;
  if (bVar1) {
    Show(this);
    return;
  }
  Hide(this);
  return;
}

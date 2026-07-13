/*
 * Entry: 004c3620
 * Name: ConstructionBlob::Control
 * Namespace: ConstructionBlob
 * Signature: void Control(ConstructionBlob * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ConstructionBlob::Control(ConstructionBlob *this)

{
  long *plVar1;
  
  plVar1 = &this->blobIndex;
  *plVar1 = *plVar1 + 1;
  if (this->blobVariance <= *plVar1) {
    *plVar1 = 0;
  }
  this->blobPtr = this->blobList;
  return;
}

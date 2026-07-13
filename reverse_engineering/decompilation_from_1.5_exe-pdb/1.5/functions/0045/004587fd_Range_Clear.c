/*
 * Entry: 004587fd
 * Name: Range::Clear
 * Namespace: Range
 * Signature: void Clear(Range * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Range::Clear(Range *this)

{
  int iVar1;
  int iVar2;
  
  iVar1 = this->height * this->width;
  this->objectCount = 0;
  iVar2 = 0;
  if (0 < iVar1) {
    do {
      this->firstObject[iVar2] = -1;
      iVar2 = iVar2 + 1;
    } while (iVar2 < iVar1);
  }
  this->curCell = 0;
  return;
}

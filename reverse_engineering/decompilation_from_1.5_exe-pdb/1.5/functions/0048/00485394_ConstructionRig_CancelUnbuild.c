/*
 * Entry: 00485394
 * Name: ConstructionRig::CancelUnbuild
 * Namespace: ConstructionRig
 * Signature: bool CancelUnbuild(ConstructionRig * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ConstructionRig::CancelUnbuild(ConstructionRig *this)

{
  if (this->unbuildHandle == 0) {
    return false;
  }
  this->unbuildHandle = 0;
  this->_padding_ = 0;
  return true;
}

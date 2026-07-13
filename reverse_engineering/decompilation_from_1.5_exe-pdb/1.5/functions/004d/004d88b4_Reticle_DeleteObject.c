/*
 * Entry: 004d88b4
 * Name: Reticle::DeleteObject
 * Namespace: Reticle
 * Signature: void DeleteObject(Reticle * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Reticle::DeleteObject(Reticle *this,GameObject *param_1)

{
  if (this->selectObj == param_1) {
    this->selectObj = (GameObject *)0x0;
  }
  return;
}

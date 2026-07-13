/*
 * Entry: 004867d2
 * Name: Craft::Packup
 * Namespace: Craft
 * Signature: void Packup(Craft * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Craft::Packup(Craft *this)

{
  if ((this->state != DEPLOYED) && (this->state != DEPLOYING)) {
    (this->vhcl->control).deploy = 0;
    return;
  }
  (this->vhcl->control).deploy = 1;
  return;
}

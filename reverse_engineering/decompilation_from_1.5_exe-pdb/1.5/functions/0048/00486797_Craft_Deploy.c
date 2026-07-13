/*
 * Entry: 00486797
 * Name: Craft::Deploy
 * Namespace: Craft
 * Signature: void Deploy(Craft * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Craft::Deploy(Craft *this)

{
  if ((this->state != UNDEPLOYED) && (this->state != UNDEPLOYING)) {
    (this->vhcl->control).deploy = 0;
    return;
  }
  (this->vhcl->control).deploy = 1;
  return;
}

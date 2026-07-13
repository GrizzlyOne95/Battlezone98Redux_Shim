/*
 * Entry: 004867c5
 * Name: Craft::IsDeployed
 * Namespace: Craft
 * Signature: bool IsDeployed(Craft * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Craft::IsDeployed(Craft *this)

{
  return this->state == DEPLOYED;
}

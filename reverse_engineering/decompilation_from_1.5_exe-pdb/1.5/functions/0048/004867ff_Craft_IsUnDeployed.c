/*
 * Entry: 004867ff
 * Name: Craft::IsUnDeployed
 * Namespace: Craft
 * Signature: bool IsUnDeployed(Craft * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Craft::IsUnDeployed(Craft *this)

{
  return this->state == UNDEPLOYED;
}

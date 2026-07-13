/*
 * Entry: 0049d038
 * Name: HoverCraft::SetAsUser
 * Namespace: HoverCraft
 * Signature: void SetAsUser(HoverCraft * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall HoverCraft::SetAsUser(HoverCraft *this)

{
  GameObject::SetAsUser((GameObject *)this);
  CleanupSound(this);
  InitSound(this);
  return;
}

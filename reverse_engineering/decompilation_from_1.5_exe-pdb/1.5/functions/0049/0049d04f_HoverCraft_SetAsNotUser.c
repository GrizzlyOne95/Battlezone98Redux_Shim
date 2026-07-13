/*
 * Entry: 0049d04f
 * Name: HoverCraft::SetAsNotUser
 * Namespace: HoverCraft
 * Signature: void SetAsNotUser(HoverCraft * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall HoverCraft::SetAsNotUser(HoverCraft *this)

{
  CleanupSound(this);
  GameObject::SetAsNotUser((GameObject *)this);
  return;
}

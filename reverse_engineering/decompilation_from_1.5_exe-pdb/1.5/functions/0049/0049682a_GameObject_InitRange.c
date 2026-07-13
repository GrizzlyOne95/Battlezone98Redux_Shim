/*
 * Entry: 0049682a
 * Name: GameObject_InitRange
 * Namespace: Global
 * Signature: void GameObject_InitRange(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GameObject_InitRange(void)

{
  Range *this;
  
  this = operator_new(0x40);
  if (this != (Range *)0x0) {
    GameObject::objectRange =
         Range::Range(this,256.0,256.0,(double)grid_rect.top,(double)grid_rect.bottom,
                      (double)grid_rect.left,(double)grid_rect.right,0x300);
    return;
  }
  GameObject::objectRange = (Range *)0x0;
  return;
}

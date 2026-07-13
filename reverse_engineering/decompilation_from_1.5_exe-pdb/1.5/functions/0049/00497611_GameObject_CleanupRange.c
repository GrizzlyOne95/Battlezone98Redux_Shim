/*
 * Entry: 00497611
 * Name: GameObject_CleanupRange
 * Namespace: Global
 * Signature: void GameObject_CleanupRange(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GameObject_CleanupRange(void)

{
  Range *pRVar1;
  
  pRVar1 = GameObject::objectRange;
  if (GameObject::objectRange != (Range *)0x0) {
    Range::~Range(GameObject::objectRange);
    operator_delete(pRVar1);
  }
  GameObject::objectRange = (Range *)0x0;
  return;
}

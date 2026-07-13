/*
 * Entry: 0045ef1e
 * Name: GetUserTarget
 * Namespace: Global
 * Signature: int GetUserTarget(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetUserTarget(void)

{
  GameObject *this;
  int iVar1;
  
  if (GameObject::userObject != (GameObject *)0x0) {
    this = GameObject::GetObj(GameObject::userObject->targetHandle);
    if (this != (GameObject *)0x0) {
      iVar1 = GameObject::GetHandle(this);
      return iVar1;
    }
  }
  return 0;
}

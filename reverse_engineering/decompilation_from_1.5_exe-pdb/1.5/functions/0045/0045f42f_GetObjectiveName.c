/*
 * Entry: 0045f42f
 * Name: GetObjectiveName
 * Namespace: Global
 * Signature: char * GetObjectiveName(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl GetObjectiveName(int param_1)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObject::GetObj(param_1);
  if (pGVar1 == (GameObject *)0x0) {
    return (char *)0x0;
  }
  return pGVar1->name;
}

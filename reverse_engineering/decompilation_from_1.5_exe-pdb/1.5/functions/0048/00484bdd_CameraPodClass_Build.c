/*
 * Entry: 00484bdd
 * Name: CameraPodClass::Build
 * Namespace: CameraPodClass
 * Signature: GameObject * Build(CameraPodClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall CameraPodClass::Build(CameraPodClass *this,_OBJ76 *param_1)

{
  CameraPod *pCVar1;
  
  pCVar1 = GameObject::operator_new(0x228);
  if (pCVar1 == (CameraPod *)0x0) {
    pCVar1 = (CameraPod *)0x0;
  }
  else {
    pCVar1 = CameraPod::CameraPod(pCVar1,param_1,this);
  }
  return (GameObject *)pCVar1;
}

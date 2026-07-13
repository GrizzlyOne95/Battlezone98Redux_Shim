/*
 * Entry: 00488f77
 * Name: Craft::GetCommand
 * Namespace: Craft
 * Signature: AiCommand GetCommand(Craft * this, VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiCommand __thiscall Craft::GetCommand(Craft *this,VECTOR_3D *param_1)

{
  int iVar1;
  AiCommand AVar2;
  
  iVar1 = GameObject::GetActiveMode((GameObject *)this);
  if ((iVar1 == 0) || (iVar1 != 1)) {
    AVar2 = CMD_NONE;
  }
  else {
    AVar2 = CMD_GO;
  }
  return AVar2;
}

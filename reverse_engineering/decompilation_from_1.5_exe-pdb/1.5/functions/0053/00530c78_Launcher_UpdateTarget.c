/*
 * Entry: 00530c78
 * Name: Launcher::UpdateTarget
 * Namespace: Launcher
 * Signature: GameObject * UpdateTarget(Launcher * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall Launcher::UpdateTarget(Launcher *this,float param_1)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObject::GetObj(this->carrier->targetHandle);
  return pGVar1;
}

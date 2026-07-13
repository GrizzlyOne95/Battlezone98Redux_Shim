/*
 * Entry: 0050ec95
 * Name: Escort_Goal::Commit_Unit
 * Namespace: Escort_Goal
 * Signature: void Commit_Unit(Escort_Goal * this, tagUNIT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Escort_Goal::Commit_Unit(Escort_Goal *this,tagUNIT *param_1)

{
  GameObject *pGVar1;
  
  if (this->_padding_ == 0) {
    pGVar1 = GameObjectHandle::GetObj(param_1->handle);
    ScavengerProcess::Increment_Escort_Count(this->damsels_ai_process,pGVar1);
  }
  return;
}

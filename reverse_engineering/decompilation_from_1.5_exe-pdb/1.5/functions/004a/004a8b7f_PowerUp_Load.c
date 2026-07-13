/*
 * Entry: 004a8b7f
 * Name: PowerUp::Load
 * Namespace: PowerUp
 * Signature: bool Load(PowerUp * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall PowerUp::Load(PowerUp *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (!missionSave) {
    ::in(param_1,&this->vhcl->flags,4);
  }
  bVar1 = GameObject::Load((GameObject *)this,param_1);
  return bVar1;
}

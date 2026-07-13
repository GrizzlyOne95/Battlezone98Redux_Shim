/*
 * Entry: 004a8bb4
 * Name: PowerUp::Save
 * Namespace: PowerUp
 * Signature: bool Save(PowerUp * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall PowerUp::Save(PowerUp *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (!missionSave) {
    ::out(param_1,&this->vhcl->flags,4,"vhclFlags");
  }
  bVar1 = GameObject::Save((GameObject *)this,param_1);
  return bVar1;
}

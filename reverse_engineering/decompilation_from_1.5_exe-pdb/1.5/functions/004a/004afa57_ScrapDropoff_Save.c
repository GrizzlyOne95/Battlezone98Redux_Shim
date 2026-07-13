/*
 * Entry: 004afa57
 * Name: ScrapDropoff::Save
 * Namespace: ScrapDropoff
 * Signature: bool Save(ScrapDropoff * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ScrapDropoff::Save(ScrapDropoff *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (!missionSave) {
    ::out(param_1,(ulong *)(*(int *)&this->field_0x220 + 0x10c),4,"vhclFlags");
  }
  bVar1 = GameObject::Save((GameObject *)this,param_1);
  return bVar1;
}

/*
 * Entry: 004b3036
 * Name: Tug::Save
 * Namespace: Tug
 * Signature: bool Save(Tug * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Tug::Save(Tug *this,_iobuf *param_1)

{
  bool bVar1;
  bool bVar2;
  
  bVar1 = out_ptr(param_1,&this->cargo,4,"undefptr");
  bVar2 = false;
  if (bVar1) {
    bVar2 = HoverCraft::Save((HoverCraft *)this,param_1);
  }
  return bVar2;
}

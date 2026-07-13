/*
 * Entry: 004b3005
 * Name: Tug::Load
 * Namespace: Tug
 * Signature: bool Load(Tug * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Tug::Load(Tug *this,_iobuf *param_1)

{
  bool bVar1;
  bool bVar2;
  
  bVar1 = in_ptr(param_1,&this->cargo,4,"Tug",this);
  bVar2 = false;
  if (bVar1) {
    bVar2 = HoverCraft::Load((HoverCraft *)this,param_1);
  }
  return bVar2;
}

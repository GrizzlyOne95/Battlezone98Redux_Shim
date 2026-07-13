/*
 * Entry: 004660fc
 * Name: TugPickup::TugPickup
 * Namespace: TugPickup
 * Signature: TugPickup * TugPickup(TugPickup * this, Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TugPickup * __thiscall TugPickup::TugPickup(TugPickup *this,Craft *param_1,GameObject *param_2)

{
  GoNear::GoNear((GoNear *)this,param_1,param_2,30.0);
  *(undefined ***)this = &_vftable_;
  return this;
}

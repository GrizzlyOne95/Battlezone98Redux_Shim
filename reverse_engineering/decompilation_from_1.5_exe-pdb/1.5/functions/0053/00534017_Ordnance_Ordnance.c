/*
 * Entry: 00534017
 * Name: Ordnance::Ordnance
 * Namespace: Ordnance
 * Signature: Ordnance * Ordnance(Ordnance * this, _OBJ76 * param_1, OrdnanceClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Ordnance * __thiscall Ordnance::Ordnance(Ordnance *this,_OBJ76 *param_1,OrdnanceClass *param_2)

{
  this->_padding_ = (int)&_vftable_;
  *(undefined4 *)&this->me = 0;
  *(undefined4 *)&(this->me).field_0x4 = 0;
  this->dt = 0.0;
  this->ordnanceClass = param_2;
  this->obj = param_1;
  this->source = 0xfa01;
  this->ordid = 0;
  this->bSend = 1;
  return this;
}

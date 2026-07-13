/*
 * Entry: 00537920
 * Name: RemoteDetonator::RemoteDetonator
 * Namespace: RemoteDetonator
 * Signature: RemoteDetonator * RemoteDetonator(RemoteDetonator * this, _OBJ76 * param_1, RemoteDetonatorClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RemoteDetonator * __thiscall
RemoteDetonator::RemoteDetonator
          (RemoteDetonator *this,_OBJ76 *param_1,RemoteDetonatorClass *param_2)

{
  Mortar::Mortar((Mortar *)this,param_1,(MortarClass *)param_2);
  this->_padding_ = (int)&_vftable_;
  this->ordnance[0] = (Ordnance *)0x0;
  this->ordnance[1] = (Ordnance *)0x0;
  this->ordnance[2] = (Ordnance *)0x0;
  this->ordnance[3] = (Ordnance *)0x0;
  this->armed = false;
  return this;
}

/*
 * Entry: 0053c664
 * Name: Torpedo::Torpedo
 * Namespace: Torpedo
 * Signature: Torpedo * Torpedo(Torpedo * this, _OBJ76 * param_1, TorpedoClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Torpedo * __thiscall Torpedo::Torpedo(Torpedo *this,_OBJ76 *param_1,TorpedoClass *param_2)

{
  PowerUp::PowerUp((PowerUp *)this,param_1,(PowerUpClass *)param_2);
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  this->lifeTimer = param_2->lifeSpan;
  return this;
}

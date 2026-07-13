/*
 * Entry: 004852a8
 * Name: ConstructionRig::ConstructionRig
 * Namespace: ConstructionRig
 * Signature: ConstructionRig * ConstructionRig(ConstructionRig * this, _OBJ76 * param_1, ConstructionRigClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ConstructionRig * __thiscall
ConstructionRig::ConstructionRig
          (ConstructionRig *this,_OBJ76 *param_1,ConstructionRigClass *param_2)

{
  Producer::Producer((Producer *)this,param_1,(ProducerClass *)param_2);
  *(undefined1 *)&this->_padding_ = 0;
  *(undefined1 *)((int)&this->_padding_ + 1) = 0;
  this->dropClass = (GameObjectClass *)0x0;
  this->unbuildHandle = 0;
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  return this;
}

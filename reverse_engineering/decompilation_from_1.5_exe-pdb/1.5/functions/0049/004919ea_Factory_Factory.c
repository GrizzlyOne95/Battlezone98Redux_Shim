/*
 * Entry: 004919ea
 * Name: Factory::Factory
 * Namespace: Factory
 * Signature: Factory * Factory(Factory * this, _OBJ76 * param_1, FactoryClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Factory * __thiscall Factory::Factory(Factory *this,_OBJ76 *param_1,FactoryClass *param_2)

{
  Producer::Producer((Producer *)this,param_1,(ProducerClass *)param_2);
  *(undefined ***)this = &_vftable__for__Attachable__;
  *(undefined ***)&this->field_0x20 = &_vftable__for__DistributedObject__;
  return this;
}

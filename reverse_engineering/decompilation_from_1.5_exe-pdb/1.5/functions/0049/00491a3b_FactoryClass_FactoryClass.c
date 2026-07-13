/*
 * Entry: 00491a3b
 * Name: FactoryClass::FactoryClass
 * Namespace: FactoryClass
 * Signature: FactoryClass * FactoryClass(FactoryClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

FactoryClass * __thiscall FactoryClass::FactoryClass(FactoryClass *this)

{
  ProducerClass::ProducerClass((ProducerClass *)this);
  *(undefined4 *)&this->field_0x144 = 2;
  *(undefined4 *)&this->field_0x148 = 2;
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0x20 = 0x46414354;
  *(char **)&this->field_0x24 = "factory";
  return this;
}

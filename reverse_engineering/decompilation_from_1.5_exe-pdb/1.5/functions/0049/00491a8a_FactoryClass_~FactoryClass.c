/*
 * Entry: 00491a8a
 * Name: FactoryClass::~FactoryClass
 * Namespace: FactoryClass
 * Signature: void ~FactoryClass(FactoryClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FactoryClass::~FactoryClass(FactoryClass *this)

{
  *(undefined ***)this = &_vftable_;
  ProducerClass::~ProducerClass((ProducerClass *)this);
  return;
}

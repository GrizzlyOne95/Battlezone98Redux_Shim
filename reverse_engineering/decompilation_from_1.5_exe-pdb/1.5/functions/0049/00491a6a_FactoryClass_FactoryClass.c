/*
 * Entry: 00491a6a
 * Name: FactoryClass::FactoryClass
 * Namespace: FactoryClass
 * Signature: FactoryClass * FactoryClass(FactoryClass * this, FactoryClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

FactoryClass * __thiscall
FactoryClass::FactoryClass(FactoryClass *this,FactoryClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  ProducerClass::ProducerClass
            ((ProducerClass *)this,(ProducerClass *)param_1,CONCAT44(unaff_ESI,(undefined4)param_2))
  ;
  *(undefined ***)this = &_vftable_;
  return this;
}

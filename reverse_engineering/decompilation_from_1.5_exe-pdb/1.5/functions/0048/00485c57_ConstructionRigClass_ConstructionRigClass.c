/*
 * Entry: 00485c57
 * Name: ConstructionRigClass::ConstructionRigClass
 * Namespace: ConstructionRigClass
 * Signature: ConstructionRigClass * ConstructionRigClass(ConstructionRigClass * this, ConstructionRigClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ConstructionRigClass * __thiscall
ConstructionRigClass::ConstructionRigClass
          (ConstructionRigClass *this,ConstructionRigClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  ProducerClass::ProducerClass
            ((ProducerClass *)this,(ProducerClass *)param_1,CONCAT44(unaff_ESI,(undefined4)param_2))
  ;
  *(undefined ***)this = &_vftable_;
  return this;
}

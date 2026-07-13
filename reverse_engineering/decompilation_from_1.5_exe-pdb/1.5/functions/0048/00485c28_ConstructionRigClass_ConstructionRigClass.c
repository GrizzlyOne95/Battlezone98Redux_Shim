/*
 * Entry: 00485c28
 * Name: ConstructionRigClass::ConstructionRigClass
 * Namespace: ConstructionRigClass
 * Signature: ConstructionRigClass * ConstructionRigClass(ConstructionRigClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ConstructionRigClass * __thiscall
ConstructionRigClass::ConstructionRigClass(ConstructionRigClass *this)

{
  ProducerClass::ProducerClass((ProducerClass *)this);
  *(undefined4 *)&this->field_0x144 = 4;
  *(undefined4 *)&this->field_0x148 = 4;
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0x20 = 0x434e5354;
  *(char **)&this->field_0x24 = "constructionrig";
  return this;
}

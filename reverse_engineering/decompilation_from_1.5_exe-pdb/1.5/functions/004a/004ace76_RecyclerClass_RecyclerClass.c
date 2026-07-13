/*
 * Entry: 004ace76
 * Name: RecyclerClass::RecyclerClass
 * Namespace: RecyclerClass
 * Signature: RecyclerClass * RecyclerClass(RecyclerClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RecyclerClass * __thiscall RecyclerClass::RecyclerClass(RecyclerClass *this)

{
  ProducerClass::ProducerClass((ProducerClass *)this);
  *(undefined4 *)&this->field_0x144 = 1;
  *(undefined4 *)&this->field_0x148 = 1;
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0x20 = 0x52435943;
  *(char **)&this->field_0x24 = "recycler";
  return this;
}

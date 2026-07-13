/*
 * Entry: 004acea5
 * Name: RecyclerClass::RecyclerClass
 * Namespace: RecyclerClass
 * Signature: RecyclerClass * RecyclerClass(RecyclerClass * this, RecyclerClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RecyclerClass * __thiscall
RecyclerClass::RecyclerClass(RecyclerClass *this,RecyclerClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  ProducerClass::ProducerClass
            ((ProducerClass *)this,(ProducerClass *)param_1,CONCAT44(unaff_ESI,(undefined4)param_2))
  ;
  *(undefined ***)this = &_vftable_;
  return this;
}

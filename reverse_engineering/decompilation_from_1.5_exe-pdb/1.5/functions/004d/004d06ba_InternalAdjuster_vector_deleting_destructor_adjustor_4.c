/*
 * Entry: 004d06ba
 * Name: InternalAdjuster::`vector_deleting_destructor'`adjustor{4}'
 * Namespace: InternalAdjuster
 * Signature: void * `vector_deleting_destructor'`adjustor{4}'(InternalAdjuster * this, uint param_1)
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* [thunk]:public: virtual void * __thiscall InternalAdjuster::`vector deleting
   destructor'`adjustor{4}' (unsigned int) */

void * __thiscall
InternalAdjuster::_vector_deleting_destructor__adjustor_4__(InternalAdjuster *this,uint param_1)

{
  void *pvVar1;
  
  pvVar1 = _scalar_deleting_destructor_((InternalAdjuster *)&this[-1].curAdjItem.field_0x4,param_1);
  return pvVar1;
}

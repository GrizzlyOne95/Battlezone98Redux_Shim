/*
 * Entry: 004b108e
 * Name: RtimeClass::RtimeClass
 * Namespace: RtimeClass
 * Signature: RtimeClass * RtimeClass(RtimeClass * this, char * param_1, _func___cdecl_SObject_ptr * param_2, RtimeClass * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RtimeClass * __thiscall
RtimeClass::RtimeClass
          (RtimeClass *this,char *param_1,_func___cdecl_SObject_ptr *param_2,RtimeClass *param_3)

{
  list<RtimeClass_*,std::allocator<RtimeClass_*>_> *this_00;
  
  if (rTimeClasses == (list<RtimeClass_*,std::allocator<RtimeClass_*>_> *)0x0) {
    this_00 = operator_new(0x1c);
    if (this_00 == (list<RtimeClass_*,std::allocator<RtimeClass_*>_> *)0x0) {
      rTimeClasses = (list<RtimeClass_*,std::allocator<RtimeClass_*>_> *)0x0;
    }
    else {
      rTimeClasses = std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::
                     list<RtimeClass_*,std::allocator<RtimeClass_*>_>(this_00);
    }
  }
  this->classname = param_1;
  this->base_class = param_3;
  this->m_pfnCreateObject = param_2;
  param_1 = (char *)this;
  std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::push_back
            (rTimeClasses,(RtimeClass **)&param_1);
  return this;
}

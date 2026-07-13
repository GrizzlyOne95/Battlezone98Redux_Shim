/*
 * Entry: 00519964
 * Name: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::_Ufill
 * Namespace: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
 * Signature: ObjectClassInfo * * _Ufill(vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * this, ObjectClassInfo * * param_1, uint param_2, ObjectClassInfo * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ObjectClassInfo ** __thiscall
std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::_Ufill
          (vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *this,
          ObjectClassInfo **param_1,uint param_2,ObjectClassInfo **param_3)

{
  stdext::unchecked_fill_n<ObjectClassInfo_*_*,unsigned_int,ObjectClassInfo_*>
            (param_1,param_2,param_3);
  return param_1 + param_2;
}

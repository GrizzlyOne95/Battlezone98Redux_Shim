/*
 * Entry: 004a151f
 * Name: std::allocator<std::pair<unsigned_int_const_,char_const_*>_>::construct
 * Namespace: std::allocator<std::pair<unsigned_int_const_,char_const_*>_>
 * Signature: void construct(allocator<std::pair<unsigned_int_const_,char_const_*>_> * this, pair<unsigned_int_const_,char_const_*> * param_1, pair<unsigned_int_const_,char_const_*> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<std::pair<unsigned_int_const_,char_const_*>_>::construct
          (allocator<std::pair<unsigned_int_const_,char_const_*>_> *this,
          pair<unsigned_int_const_,char_const_*> *param_1,
          pair<unsigned_int_const_,char_const_*> *param_2)

{
  _Construct<std::pair<unsigned_int_const_,char_const_*>,std::pair<unsigned_int_const_,char_const_*>_>
            (param_1,param_2);
  return;
}

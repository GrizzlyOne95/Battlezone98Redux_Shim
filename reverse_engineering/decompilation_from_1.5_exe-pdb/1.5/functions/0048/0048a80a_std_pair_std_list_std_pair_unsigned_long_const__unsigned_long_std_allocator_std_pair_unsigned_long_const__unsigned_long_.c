/*
 * Entry: 0048a80a
 * Name: std::pair<std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>,bool>::pair<std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>,bool>
 * Namespace: std::pair<std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>,bool>
 * Signature: pair<std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>,bool> * pair<std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>,bool>(pair<std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>,bool> * this, _Iterator<1> * param_1, bool * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>,bool>
* __thiscall
std::
pair<std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>,bool>
::
pair<std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>,bool>
          (pair<std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>,bool>
           *this,_Iterator<1> *param_1,bool *param_2)

{
  *(undefined4 *)&this->first = *(undefined4 *)param_1;
  *(undefined4 *)&(this->first).field_0x4 = *(undefined4 *)&param_1->field_0x4;
  this->second = *param_2;
  return this;
}

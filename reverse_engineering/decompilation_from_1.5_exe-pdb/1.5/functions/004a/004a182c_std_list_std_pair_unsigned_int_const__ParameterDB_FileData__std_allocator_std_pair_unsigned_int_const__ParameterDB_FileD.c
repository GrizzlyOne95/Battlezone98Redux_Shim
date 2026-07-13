/*
 * Entry: 004a182c
 * Name: std::list<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>::clear
 * Namespace: std::list<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>
 * Signature: void clear(list<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::
list<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>
::clear(list<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>
        *this)

{
  _Node *p_Var1;
  _Node *p_Var2;
  
  p_Var1 = this->_Myhead;
  p_Var2 = p_Var1->_Next;
  p_Var1->_Next = p_Var1;
  this->_Myhead->_Prev = this->_Myhead;
  this->_Mysize = 0;
  if (p_Var2 != this->_Myhead) {
    do {
      p_Var1 = p_Var2->_Next;
      operator_delete(p_Var2);
      p_Var2 = p_Var1;
    } while (p_Var1 != this->_Myhead);
  }
  return;
}

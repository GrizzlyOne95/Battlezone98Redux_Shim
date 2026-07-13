/*
 * Entry: 0051c059
 * Name: matrix<unsigned_char>::`scalar_deleting_destructor'
 * Namespace: matrix<unsigned_char>
 * Signature: void * `scalar_deleting_destructor'(matrix<unsigned_char> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
matrix<unsigned_char>::_scalar_deleting_destructor_(matrix<unsigned_char> *this,uint param_1)

{
  Clean_Up(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

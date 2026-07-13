/*
 * Entry: 0051711f
 * Name: matrix<unsigned_char>::operator()
 * Namespace: matrix<unsigned_char>
 * Signature: uchar * operator()(matrix<unsigned_char> * this, int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar * __thiscall
matrix<unsigned_char>::operator()(matrix<unsigned_char> *this,int param_1,int param_2)

{
  return this->data + param_2 + this->columns * param_1;
}

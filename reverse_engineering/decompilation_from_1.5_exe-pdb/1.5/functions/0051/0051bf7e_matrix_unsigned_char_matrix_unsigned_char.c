/*
 * Entry: 0051bf7e
 * Name: matrix<unsigned_char>::matrix<unsigned_char>
 * Namespace: matrix<unsigned_char>
 * Signature: matrix<unsigned_char> * matrix<unsigned_char>(matrix<unsigned_char> * this, int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

matrix<unsigned_char> * __thiscall
matrix<unsigned_char>::matrix<unsigned_char>(matrix<unsigned_char> *this,int param_1,int param_2)

{
  this->data = (uchar *)0x0;
  Allocate(this,param_1,param_2);
  return this;
}

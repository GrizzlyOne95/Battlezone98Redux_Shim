/*
 * Entry: 0051bf97
 * Name: matrix<unsigned_char>::~matrix<unsigned_char>
 * Namespace: matrix<unsigned_char>
 * Signature: void ~matrix<unsigned_char>(matrix<unsigned_char> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall matrix<unsigned_char>::~matrix<unsigned_char>(matrix<unsigned_char> *this)

{
  if (this->data != (uchar *)0x0) {
    free(this->data);
  }
  this->data = (uchar *)0x0;
  this->size = 0;
  return;
}

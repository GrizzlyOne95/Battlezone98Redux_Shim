/*
 * Entry: 0051bf64
 * Name: matrix<unsigned_char>::Clean_Up
 * Namespace: matrix<unsigned_char>
 * Signature: void Clean_Up(matrix<unsigned_char> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall matrix<unsigned_char>::Clean_Up(matrix<unsigned_char> *this)

{
  if (this->data != (uchar *)0x0) {
    free(this->data);
  }
  this->data = (uchar *)0x0;
  this->size = 0;
  return;
}

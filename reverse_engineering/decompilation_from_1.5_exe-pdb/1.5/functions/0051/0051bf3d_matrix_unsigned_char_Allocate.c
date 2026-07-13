/*
 * Entry: 0051bf3d
 * Name: matrix<unsigned_char>::Allocate
 * Namespace: matrix<unsigned_char>
 * Signature: void Allocate(matrix<unsigned_char> * this, int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall matrix<unsigned_char>::Allocate(matrix<unsigned_char> *this,int param_1,int param_2)

{
  uchar *puVar1;
  
  this->size = param_1 * param_2;
  this->rows = param_1;
  this->columns = param_2;
  puVar1 = malloc(param_1 * param_2);
  this->data = puVar1;
  return;
}

/*
 * Entry: 004a0709
 * Name: std::pair<unsigned_int_const_,char_const_*>::pair<unsigned_int_const_,char_const_*>
 * Namespace: std::pair<unsigned_int_const_,char_const_*>
 * Signature: pair<unsigned_int_const_,char_const_*> * pair<unsigned_int_const_,char_const_*>(pair<unsigned_int_const_,char_const_*> * this, uint * param_1, char * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<unsigned_int_const_,char_const_*> * __thiscall
std::pair<unsigned_int_const_,char_const_*>::pair<unsigned_int_const_,char_const_*>
          (pair<unsigned_int_const_,char_const_*> *this,uint *param_1,char **param_2)

{
  this->first = *param_1;
  this->second = *param_2;
  return this;
}

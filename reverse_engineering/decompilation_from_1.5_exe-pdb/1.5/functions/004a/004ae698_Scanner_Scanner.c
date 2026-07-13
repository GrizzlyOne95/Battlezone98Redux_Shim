/*
 * Entry: 004ae698
 * Name: Scanner::Scanner
 * Namespace: Scanner
 * Signature: Scanner * Scanner(Scanner * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Scanner * __thiscall Scanner::Scanner(Scanner *this,GameObject *param_1)

{
  this->range = 200.0;
  this->owner = param_1;
  this->period = 0.0;
  this->sweep = 0.0;
  this->active = false;
  param_1 = (GameObject *)this;
  std::vector<Scanner_*,std::allocator<Scanner_*>_>::push_back(&scannerList,(Scanner **)&param_1);
  return this;
}

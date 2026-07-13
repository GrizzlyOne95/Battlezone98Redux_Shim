/*
 * Entry: 00549aa8
 * Name: Addr::Addr
 * Namespace: Addr
 * Signature: Addr * Addr(Addr * this, void * * param_1, void * param_2, char * param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Addr * __thiscall Addr::Addr(Addr *this,void **param_1,void *param_2,char *param_3,void *param_4)

{
  list<Addr_*,std::allocator<Addr_*>_> *this_00;
  
  this->address = param_1;
  this->pointer = param_2;
  this->classname = param_3;
  this->classpointer = param_4;
  if (table == (list<Addr_*,std::allocator<Addr_*>_> *)0x0) {
    this_00 = operator_new(0x1c);
    if (this_00 == (list<Addr_*,std::allocator<Addr_*>_> *)0x0) {
      table = (list<Addr_*,std::allocator<Addr_*>_> *)0x0;
    }
    else {
      table = std::list<Addr_*,std::allocator<Addr_*>_>::list<Addr_*,std::allocator<Addr_*>_>
                        (this_00);
    }
  }
  param_1 = &this->address;
  std::list<Addr_*,std::allocator<Addr_*>_>::push_back(table,(Addr **)&param_1);
  return this;
}

/*
 * Entry: 004613f9
 * Name: std::vector<Scrap_*,std::allocator<Scrap_*>_>::front
 * Namespace: std::vector<Scrap_*,std::allocator<Scrap_*>_>
 * Signature: Scrap * * front(vector<Scrap_*,std::allocator<Scrap_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Scrap ** __thiscall
std::vector<Scrap_*,std::allocator<Scrap_*>_>::front(vector<Scrap_*,std::allocator<Scrap_*>_> *this)

{
  Scrap **ppSVar1;
  _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Myptr = (Scrap **)this;
  _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::
  _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>
            (&local_c,this->_Myfirst,(_Container_base_aux *)this);
  ppSVar1 = _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::operator*(&local_c);
  return ppSVar1;
}

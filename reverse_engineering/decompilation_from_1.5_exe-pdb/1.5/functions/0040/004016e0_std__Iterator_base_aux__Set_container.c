/*
 * Entry: 004016e0
 * Name: std::_Iterator_base_aux::_Set_container
 * Namespace: std::_Iterator_base_aux
 * Signature: void _Set_container(_Iterator_base_aux * this, _Container_base_aux * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Iterator_base_aux::_Set_container(_Iterator_base_aux *this,_Container_base_aux *param_1)

{
  this->_Myaux = param_1->_Myownedaux;
  return;
}

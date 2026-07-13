/*
 * Entry: 004016f7
 * Name: std::_Iterator_base_aux::_Same_container
 * Namespace: std::_Iterator_base_aux
 * Signature: bool _Same_container(_Iterator_base_aux * this, _Iterator_base_aux * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::_Iterator_base_aux::_Same_container(_Iterator_base_aux *this,_Iterator_base_aux *param_1)

{
  return (bool)('\x01' - (this->_Myaux != param_1->_Myaux));
}

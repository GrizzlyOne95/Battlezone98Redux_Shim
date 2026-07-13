/*
 * Entry: 004016eb
 * Name: std::_Iterator_base_aux::_Getmycont
 * Namespace: std::_Iterator_base_aux
 * Signature: _Container_base_aux * _Getmycont(_Iterator_base_aux * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Container_base_aux * __thiscall std::_Iterator_base_aux::_Getmycont(_Iterator_base_aux *this)

{
  if (this->_Myaux != (_Aux_cont *)0x0) {
    return this->_Myaux->_Mycontainer;
  }
  return (_Container_base_aux *)0x0;
}

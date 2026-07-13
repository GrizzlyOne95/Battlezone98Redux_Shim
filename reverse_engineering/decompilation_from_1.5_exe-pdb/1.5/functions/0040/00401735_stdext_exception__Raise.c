/*
 * Entry: 00401735
 * Name: stdext::exception::_Raise
 * Namespace: stdext::exception
 * Signature: void _Raise(exception * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall stdext::exception::_Raise(exception *this)

{
  if (_DAT_00225350 != (code *)0x0) {
    (*_DAT_00225350)(this);
  }
  (**(code **)(this->_padding_ + 8))();
  std::_Throw(this);
  return;
}

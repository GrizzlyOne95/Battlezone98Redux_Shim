/*
 * Entry: 00401841
 * Name: std::length_error::~length_error
 * Namespace: std::length_error
 * Signature: void ~length_error(length_error * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall std::length_error::~length_error(length_error *this)

{
  *(undefined ***)this = &_vftable_;
  logic_error::~logic_error((logic_error *)this);
  return;
}

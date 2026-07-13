/*
 * Entry: 004055ef
 * Name: std::out_of_range::~out_of_range
 * Namespace: std::out_of_range
 * Signature: void ~out_of_range(out_of_range * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall std::out_of_range::~out_of_range(out_of_range *this)

{
  *(undefined ***)this = &_vftable_;
  logic_error::~logic_error((logic_error *)this);
  return;
}

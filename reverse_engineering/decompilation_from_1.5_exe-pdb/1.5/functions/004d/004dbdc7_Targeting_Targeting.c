/*
 * Entry: 004dbdc7
 * Name: Targeting::Targeting
 * Namespace: Targeting
 * Signature: Targeting * Targeting(Targeting * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Targeting * __thiscall Targeting::Targeting(Targeting *this)

{
  DisplayInterface::DisplayInterface((DisplayInterface *)this);
  *(undefined ***)this = &_vftable_;
  DisplayInterface::AddView((DisplayInterface *)this,0,-2);
  DisplayInterface::AddView((DisplayInterface *)this,2,-2);
  DisplayInterface::AddView((DisplayInterface *)this,1,-2);
  DisplayInterface::AddView((DisplayInterface *)this,3,-2);
  DisplayInterface::AddView((DisplayInterface *)this,7,-2);
  return this;
}

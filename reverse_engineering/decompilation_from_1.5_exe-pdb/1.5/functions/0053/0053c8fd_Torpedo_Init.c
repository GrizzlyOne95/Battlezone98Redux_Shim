/*
 * Entry: 0053c8fd
 * Name: Torpedo::Init
 * Namespace: Torpedo
 * Signature: void Init(Torpedo * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Torpedo::Init(Torpedo *this,int param_1)

{
  PowerUp::Init((PowerUp *)this,param_1);
  this->soundThrust = (_gas_object *)0x0;
  return;
}

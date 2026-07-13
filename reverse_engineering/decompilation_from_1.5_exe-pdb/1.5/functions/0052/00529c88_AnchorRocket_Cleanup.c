/*
 * Entry: 00529c88
 * Name: AnchorRocket::Cleanup
 * Namespace: AnchorRocket
 * Signature: void Cleanup(AnchorRocket * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AnchorRocket::Cleanup(AnchorRocket *this)

{
  uint *puVar1;
  
  puVar1 = (uint *)(this->_padding_ + 0x14);
  *puVar1 = *puVar1 & 0xfffffff7;
  Bullet::Cleanup((Bullet *)this);
  return;
}

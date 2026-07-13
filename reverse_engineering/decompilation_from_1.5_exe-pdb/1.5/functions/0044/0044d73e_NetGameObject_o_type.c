/*
 * Entry: 0044d73e
 * Name: NetGameObject::o_type
 * Namespace: NetGameObject
 * Signature: char o_type(NetGameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char __thiscall NetGameObject::o_type(NetGameObject *this)

{
  if (this->field_0x88 == '\0') {
    return 'U';
  }
  return ((this->field_0x88 != '\x01') - 1U & 0xfa) + 0x52;
}

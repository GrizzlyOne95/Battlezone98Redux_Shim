/*
 * Entry: 004d53e5
 * Name: NetDisplayObject::o_type
 * Namespace: NetDisplayObject
 * Signature: char o_type(NetDisplayObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char __thiscall NetDisplayObject::o_type(NetDisplayObject *this)

{
  if (this->field_0x88 == '\0') {
    return 'U';
  }
  return ((this->field_0x88 != '\x01') - 1U & 0xfa) + 0x52;
}

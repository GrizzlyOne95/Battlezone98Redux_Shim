/*
 * Entry: 005306fa
 * Name: ImageRefract::Activate
 * Namespace: ImageRefract
 * Signature: void Activate(ImageRefract * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ImageRefract::Activate(ImageRefract *this)

{
  uint *puVar1;
  
  obj_set_flag(*(_OBJ76 **)&this->field_0x18,1);
  puVar1 = (uint *)(*(int *)&this->field_0x18 + 0x14);
  *puVar1 = *puVar1 & 0xfffffffe;
  puVar1 = (uint *)(*(int *)&this->field_0x18 + 0x14);
  *puVar1 = *puVar1 | 0x400;
  return;
}

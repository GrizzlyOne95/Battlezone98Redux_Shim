/*
 * Entry: 0053071c
 * Name: ImageRefract::Deactivate
 * Namespace: ImageRefract
 * Signature: void Deactivate(ImageRefract * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ImageRefract::Deactivate(ImageRefract *this)

{
  uint *puVar1;
  
  obj_clear_flag(*(_OBJ76 **)&this->field_0x18,1);
  puVar1 = (uint *)(*(int *)&this->field_0x18 + 0x14);
  *puVar1 = *puVar1 & 0xfffffbff;
  return;
}

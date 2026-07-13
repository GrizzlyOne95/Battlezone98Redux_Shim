/*
 * Entry: 005306ed
 * Name: ImageRefract::IsActive
 * Namespace: ImageRefract
 * Signature: bool IsActive(ImageRefract * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ImageRefract::IsActive(ImageRefract *this)

{
  return (bool)((byte)(*(uint *)(*(int *)&this->field_0x18 + 0x14) >> 10) & 1);
}

/*
 * Entry: 004afd72
 * Name: ScrapField::Simulate
 * Namespace: ScrapField
 * Signature: void Simulate(ScrapField * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScrapField::Simulate(ScrapField *this,float param_1)

{
  bool bVar1;
  
  bVar1 = DistributedObject::IsRemote((DistributedObject *)&this->field_0x20);
  if (!bVar1) {
    MakeScrapField((VECTOR_3D *)&this->field_0xfc,*(int *)(*(int *)&this->field_0xec + 0x54));
    (**(code **)(*(int *)&this->field_0x20 + 0x10))();
  }
  return;
}

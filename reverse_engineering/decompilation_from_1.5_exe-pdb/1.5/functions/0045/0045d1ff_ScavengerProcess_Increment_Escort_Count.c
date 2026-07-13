/*
 * Entry: 0045d1ff
 * Name: ScavengerProcess::Increment_Escort_Count
 * Namespace: ScavengerProcess
 * Signature: void Increment_Escort_Count(ScavengerProcess * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScavengerProcess::Increment_Escort_Count(ScavengerProcess *this,GameObject *param_1)

{
  void *pvVar1;
  
  if (param_1 == (GameObject *)0x0) {
    pvVar1 = (void *)0x0;
  }
  else {
    pvVar1 = (void *)GameObject::GetHandle(param_1);
  }
  C_Linked_List_Add_Data(this->my_escorts,pvVar1);
  return;
}

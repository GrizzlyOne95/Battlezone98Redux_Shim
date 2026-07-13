/*
 * Entry: 0045cc52
 * Name: ScavengerProcess::Decrement_Escort_Count
 * Namespace: ScavengerProcess
 * Signature: void Decrement_Escort_Count(ScavengerProcess * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScavengerProcess::Decrement_Escort_Count(ScavengerProcess *this,int param_1)

{
  C_Linked_List_Remove_Data(this->my_escorts,(void *)param_1);
  return;
}

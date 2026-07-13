/*
 * Entry: 0045cc46
 * Name: ScavengerProcess::Get_Escort_Count
 * Namespace: ScavengerProcess
 * Signature: int Get_Escort_Count(ScavengerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall ScavengerProcess::Get_Escort_Count(ScavengerProcess *this)

{
  if (this->my_escorts == (tag_c_linked_list *)0x0) {
    return 0;
  }
  return this->my_escorts->count;
}

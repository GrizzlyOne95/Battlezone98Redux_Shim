/*
 * Entry: 00517d48
 * Name: Glue_Check_Unit
 * Namespace: Global
 * Signature: void Glue_Check_Unit(tagUNIT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Glue_Check_Unit(tagUNIT *param_1)

{
  GameObjectHandle::GetObj(param_1->handle);
  return;
}

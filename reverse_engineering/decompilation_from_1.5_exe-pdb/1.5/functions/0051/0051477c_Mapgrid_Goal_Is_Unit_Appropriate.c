/*
 * Entry: 0051477c
 * Name: Mapgrid_Goal::Is_Unit_Appropriate
 * Namespace: Mapgrid_Goal
 * Signature: int Is_Unit_Appropriate(Mapgrid_Goal * this, tagUNIT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall Mapgrid_Goal::Is_Unit_Appropriate(Mapgrid_Goal *this,tagUNIT *param_1)

{
  int iVar1;
  
  iVar1 = Squad_Unit_Is_Appropriate(param_1,this);
  return iVar1;
}

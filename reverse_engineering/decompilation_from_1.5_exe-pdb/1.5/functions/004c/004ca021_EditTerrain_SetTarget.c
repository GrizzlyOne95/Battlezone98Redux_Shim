/*
 * Entry: 004ca021
 * Name: EditTerrain::SetTarget
 * Namespace: EditTerrain
 * Signature: void SetTarget(EditTerrain * this, VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EditTerrain::SetTarget(EditTerrain *this,VECTOR_3D *param_1)

{
  (this->viewCenter).x = param_1->x;
  (this->viewCenter).y = param_1->y;
  (this->viewCenter).z = param_1->z;
  return;
}

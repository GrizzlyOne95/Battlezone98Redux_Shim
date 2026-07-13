/*
 * Entry: 00525849
 * Name: GetClsnPlanes
 * Namespace: Global
 * Signature: CLSN_BOXES * GetClsnPlanes(VDF_COLLISION_PLANES * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CLSN_BOXES * __cdecl GetClsnPlanes(VDF_COLLISION_PLANES *param_1)

{
  CLSN_BOXES *pCVar1;
  
  pCVar1 = malloc(0x3c);
  if (pCVar1 != (CLSN_BOXES *)0x0) {
    pCVar1->nz = 4;
    pCVar1->ny = 4;
    pCVar1->nx = 4;
    pCVar1->x[0] = param_1->left;
    pCVar1->x[1] = param_1->left_middle;
    pCVar1->x[2] = param_1->right_middle;
    pCVar1->x[3] = param_1->right;
    pCVar1->y[0] = param_1->bottom;
    pCVar1->y[1] = param_1->bottom_middle;
    pCVar1->y[2] = param_1->top_middle;
    pCVar1->y[3] = param_1->top;
    pCVar1->z[0] = param_1->back;
    pCVar1->z[1] = param_1->back_middle;
    pCVar1->z[2] = param_1->front_middle;
    pCVar1->z[3] = param_1->front;
  }
  return pCVar1;
}

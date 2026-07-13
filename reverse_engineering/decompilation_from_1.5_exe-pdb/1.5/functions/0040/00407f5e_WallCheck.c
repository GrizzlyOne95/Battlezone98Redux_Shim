/*
 * Entry: 00407f5e
 * Name: WallCheck
 * Namespace: Global
 * Signature: bool WallCheck(uint param_1, uint param_2, uint param_3, DirType param_4, DirType param_5, GameObject * param_6, VECTOR_3D * param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl
WallCheck(uint param_1,uint param_2,uint param_3,DirType param_4,DirType param_5,GameObject *param_6
         ,VECTOR_3D *param_7)

{
  float fVar1;
  float fVar2;
  DirType DVar3;
  
  if (((param_1 & param_2) != param_2) || ((param_3 & param_1) != 0)) {
    return false;
  }
  fVar1 = 0.0;
  if (param_4 == ~DIR_UP) {
    param_4 = DIR_LEFT;
    if ((param_5 == DIR_UP) || (param_5 == DIR_DOWN)) {
      if (0.0 < (param_6->euler).v.x) goto LAB_00407fca;
    }
    else if ((param_6->euler).v.z <= 0.0) {
LAB_00407fca:
      param_4 = DIR_RIGHT;
    }
    if ((param_5 == DIR_LEFT) || (param_5 == DIR_DOWN)) {
      param_4 = param_4 - DIR_DOWN & DIR_LEFT;
    }
  }
  if (param_4 != DIR_UP) {
    if (param_4 == DIR_RIGHT) {
      param_5 = param_5 + DIR_RIGHT;
    }
    else {
      param_5 = param_5 + DIR_LEFT;
    }
  }
  DVar3 = param_5 & DIR_LEFT;
  if (DVar3 == DIR_UP) {
    param_7->x = 0.0;
    fVar1 = 20.0;
  }
  else {
    if (DVar3 == DIR_RIGHT) {
      fVar2 = 20.0;
    }
    else {
      if (DVar3 == DIR_DOWN) {
        param_7->x = 0.0;
        fVar1 = -20.0;
        goto LAB_00408006;
      }
      if (DVar3 != DIR_LEFT) {
        return true;
      }
      fVar2 = -20.0;
    }
    param_7->x = fVar2;
  }
LAB_00408006:
  param_7->z = fVar1;
  return true;
}

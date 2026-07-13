/*
 * Entry: 00474af9
 * Name: inside_polyxz
 * Namespace: Global
 * Signature: int inside_polyxz(_clsn_poly * param_1, VECTOR_3D * param_2, float param_3, float param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl inside_polyxz(_clsn_poly *param_1,VECTOR_3D *param_2,float param_3,float param_4)

{
  float fVar1;
  bool bVar2;
  bool bVar3;
  _clsn_poly *p_Var4;
  VECTOR_3D *pVVar5;
  VECTOR_3D *pVVar6;
  ushort *puVar7;
  int iVar8;
  ushort *puVar9;
  int local_10;
  
  p_Var4 = param_1;
  iVar8 = param_1->vtx_count;
  bVar2 = false;
  bVar3 = false;
  param_1 = (_clsn_poly *)0x0;
  if (iVar8 == 0) {
    return 0;
  }
  puVar7 = p_Var4->vtxlist + iVar8;
  puVar9 = puVar7;
  local_10 = iVar8;
  while( true ) {
    local_10 = local_10 + -1;
    puVar9 = puVar9 + -1;
    if (param_3 < param_2[*puVar9].x) {
      param_1 = (_clsn_poly *)((uint)param_1 | 2);
    }
    else {
      param_1 = (_clsn_poly *)((uint)param_1 | 1);
    }
    if (param_4 < param_2[*puVar9].z) {
      param_1 = (_clsn_poly *)((uint)param_1 | 8);
    }
    else {
      param_1 = (_clsn_poly *)((uint)param_1 | 4);
    }
    if (param_1 == (_clsn_poly *)0xf) break;
    if (local_10 == 0) {
      return 0;
    }
  }
  pVVar5 = param_2 + *p_Var4->vtxlist;
  do {
    iVar8 = iVar8 + -1;
    puVar7 = puVar7 + -1;
    pVVar6 = param_2 + *puVar7;
    if (((param_4 <= pVVar6->z) || (param_4 <= pVVar5->z)) &&
       ((pVVar6->z <= param_4 || (pVVar5->z <= param_4)))) {
      if ((param_4 == pVVar6->z) && (param_4 == pVVar5->z)) {
        if ((pVVar6->x < param_3) && (pVVar5->x < param_3)) {
          return 0;
        }
        if (pVVar6->x <= param_3) {
          return 1;
        }
        if (param_3 < pVVar5->x) {
          return 0;
        }
        return 1;
      }
      if (param_4 != pVVar6->z) {
        if ((param_3 <= pVVar6->x) || (param_3 <= pVVar5->x)) {
          if ((pVVar6->x <= param_3) || (pVVar5->x <= param_3)) {
            fVar1 = (((param_4 - pVVar6->z) * (pVVar5->x - pVVar6->x)) / (pVVar5->z - pVVar6->z) +
                    pVVar6->x) - param_3;
            if (fVar1 < 0.0) goto LAB_00474c01;
            if (fVar1 <= 0.0) {
              return 1;
            }
          }
          if (bVar3) {
            return 0;
          }
          if (bVar2) {
            return 1;
          }
          bVar3 = true;
        }
        else {
LAB_00474c01:
          if (bVar2) {
            return 0;
          }
          if (bVar3) {
            return 1;
          }
          bVar2 = true;
        }
      }
    }
    pVVar5 = pVVar6;
    if (iVar8 == 0) {
      return 0;
    }
  } while( true );
}

/*
 * Entry: 004762b6
 * Name: PointEntityCheck
 * Namespace: Global
 * Signature: int PointEntityCheck(POINT_VEL param_1, tagENTITY * param_2, float param_3, _OBJ76 * * param_4, float * param_5, VECTOR_3D * param_6, float param_7, int param_8)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
PointEntityCheck(POINT_VEL param_1,tagENTITY *param_2,float param_3,_OBJ76 **param_4,float *param_5,
                VECTOR_3D *param_6,float param_7,int param_8)

{
  CLSN_TYPE CVar1;
  POINT_VEL PVar2;
  POINT_VEL PVar3;
  int iVar4;
  float unaff_EDI;
  undefined4 *puVar5;
  undefined4 in_stack_ffffffc0;
  undefined4 in_stack_ffffffc4;
  undefined1 in_stack_ffffffc8 [16];
  undefined1 auVar6 [12];
  undefined4 in_stack_ffffffd8;
  float in_stack_ffffffdc;
  
  CVar1 = param_2->cType;
  if (CVar1 == CLSN_TYPE_CAR) {
    puVar5 = (undefined4 *)&stack0xffffffc8;
    for (iVar4 = 6; register0x00000010 = (BADSPACEBASE *)((int)register0x00000010 + 4), iVar4 != 0;
        iVar4 = iVar4 + -1) {
      *puVar5 = *(undefined4 *)register0x00000010;
      puVar5 = puVar5 + 1;
    }
    PVar3.v.y = (float)in_stack_ffffffd8;
    auVar6 = in_stack_ffffffc8._0_12_;
    PVar3.p.x = (float)auVar6._0_4_;
    PVar3.p.y = (float)auVar6._4_4_;
    PVar3.p.z = (float)auVar6._8_4_;
    PVar3.v.x = (float)in_stack_ffffffc8._12_4_;
    PVar3.v.z = in_stack_ffffffdc;
    iVar4 = PointCarCheck(PVar3,(tagENTITY *)param_3,(float)param_5,&param_6->x,(VECTOR_3D *)param_7
                          ,unaff_EDI);
    if (iVar4 == 0) {
      return 0;
    }
  }
  else {
    if (CVar1 != CLSN_TYPE_SPHERE) {
      if (CVar1 != CLSN_TYPE_CHILDREN) {
        return 0;
      }
      puVar5 = (undefined4 *)&stack0xffffffc0;
      for (iVar4 = 6; register0x00000010 = (BADSPACEBASE *)((int)register0x00000010 + 4), iVar4 != 0
          ; iVar4 = iVar4 + -1) {
        *puVar5 = *(undefined4 *)register0x00000010;
        puVar5 = puVar5 + 1;
      }
      PVar2.p.y = (float)in_stack_ffffffc4;
      PVar2.p.x = (float)in_stack_ffffffc0;
      auVar6 = in_stack_ffffffc8._4_12_;
      PVar2.p.z = (float)in_stack_ffffffc8._0_4_;
      PVar2.v.x = (float)auVar6._0_4_;
      PVar2.v.y = (float)auVar6._4_4_;
      PVar2.v.z = (float)auVar6._8_4_;
      iVar4 = PointHierarchyCheck(PVar2,(tagENTITY *)param_3,(float)param_4,(_OBJ76 **)param_5,
                                  &param_6->x,(VECTOR_3D *)param_7,(float)param_8,(int)unaff_EDI);
      return iVar4;
    }
    iVar4 = 1;
  }
  *param_4 = param_2->obj76;
  return iVar4;
}

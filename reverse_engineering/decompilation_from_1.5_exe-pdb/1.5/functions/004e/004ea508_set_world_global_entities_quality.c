/*
 * Entry: 004ea508
 * Name: set_world_global_entities_quality
 * Namespace: Global
 * Signature: void set_world_global_entities_quality(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl set_world_global_entities_quality(void)

{
  _OBJ76 *p_Var1;
  int iVar2;
  int iVar3;
  long lVar4;
  tagENTITY *ptVar5;
  long lVar6;
  long local_4;
  
  local_4 = -1;
  if ((UserProfilePtr->graphicDetail).vehTex == '\0') {
    local_4 = -0x15;
  }
  lVar4 = -1;
  if ((UserProfilePtr->graphicDetail).objTex == '\0') {
    lVar4 = -0x15;
  }
  iVar3 = 0;
  if (0 < world_count) {
    ptVar5 = world;
    do {
      p_Var1 = ptVar5->obj76;
      if (p_Var1 != (_OBJ76 *)0x0) {
        iVar2 = dynamic_object(p_Var1);
        lVar6 = lVar4;
        if (iVar2 == 1) {
          lVar6 = local_4;
        }
        Obj_Set_Texture_Quality(p_Var1,lVar6);
      }
      iVar3 = iVar3 + 1;
      ptVar5 = ptVar5 + 1;
    } while (iVar3 < world_count);
  }
  return;
}

/*
 * Entry: 004ec90c
 * Name: create_obj
 * Namespace: Global
 * Signature: _OBJ76 * create_obj(_OBJ76 * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_OBJ76 * __cdecl create_obj(_OBJ76 *param_1,char *param_2)

{
  _OBJ76 *p_Var1;
  ushort uVar2;
  _OBJ76 *p_Var3;
  int iVar4;
  MAT_3D *pMVar5;
  MAT_3D *pMVar6;
  
  p_Var3 = free_head;
  if (free_head == (_OBJ76 *)0x0) {
    p_Var3 = calloc(1,0xf0);
  }
  else {
    free_head = free_head->sibling;
    memset(p_Var3,0);
  }
  iVar4 = obj_seq_no;
  p_Var3->render_type_override = -1;
  p_Var3->NavGroup = -1;
  p_Var3->flags = 0;
  p_Var3->parent = (_OBJ76 *)0x0;
  p_Var3->child = (_OBJ76 *)0x0;
  p_Var3->sibling = (_OBJ76 *)0x0;
  p_Var3->geom = (_GEOMETRY *)0x0;
  (p_Var3->objHandle).handle = iVar4 << 0xb;
  p_Var3->gravestone = 0;
  (p_Var3->reps).repCount = 0;
  (p_Var3->reps).repSlots = 0;
  (p_Var3->reps).repNum = 0;
  (p_Var3->reps).reps = (_REP_INFO *)0x0;
  (p_Var3->bSphere).radius = 0.0;
  p_Var3->class_id = CLASS_ID_NONE;
  p_Var3->class_ptr = (void *)0x0;
  p_Var3->dibs = (dibs_stack *)0x0;
  p_Var3->createdby = (dibs_stack *)0x0;
  p_Var3->removedby = (dibs_stack *)0x0;
  p_Var3->clsnInfo = (void *)0x0;
  (p_Var3->bSphere).origin.x = 0.0;
  (p_Var3->bSphere).origin.y = 0.0;
  (p_Var3->bSphere).origin.z = 0.0;
  obj_seq_no = obj_seq_no + 1;
  (p_Var3->bBox).max.x = 0.0;
  (p_Var3->bBox).max.y = 0.0;
  (p_Var3->bBox).max.z = 0.0;
  (p_Var3->bBox).min.x = 0.0;
  (p_Var3->bBox).min.y = 0.0;
  (p_Var3->bBox).min.z = 0.0;
  pMVar5 = &Identity_Matrix;
  pMVar6 = &p_Var3->transform;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar6->right_x = pMVar5->right_x;
    pMVar5 = (MAT_3D *)&pMVar5->right_y;
    pMVar6 = (MAT_3D *)&pMVar6->right_y;
  }
  if (param_1 == (_OBJ76 *)0x0) {
    uVar2 = 1;
    current_node = p_Var3;
    obj_tree_head = p_Var3;
  }
  else {
    p_Var1 = param_1->child;
    if (p_Var1 != (_OBJ76 *)0x0) {
      p_Var3->sibling = p_Var1;
    }
    p_Var3->parent = param_1;
    param_1->child = p_Var3;
    p_Var3->gravestone = param_1->gravestone;
    uVar2 = param_1->counter;
  }
  p_Var3->counter = uVar2;
  return p_Var3;
}

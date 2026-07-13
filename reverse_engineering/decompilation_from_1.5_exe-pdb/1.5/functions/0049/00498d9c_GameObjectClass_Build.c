/*
 * Entry: 00498d9c
 * Name: GameObjectClass::Build
 * Namespace: GameObjectClass
 * Signature: GameObject * Build(GameObjectClass * this, MAT_3D * param_1, int param_2, int param_3, int param_4, char * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

GameObject * __thiscall
GameObjectClass::Build
          (GameObjectClass *this,MAT_3D *param_1,int param_2,int param_3,int param_4,char *param_5)

{
  VECTOR_3D VVar1;
  undefined4 *puVar2;
  short sVar3;
  VECTOR_3D *pVVar4;
  CLSN_BOXES *pCVar5;
  tagENTITY *ptVar6;
  int iVar7;
  GameObject *this_00;
  MAT_3D *pMVar8;
  undefined4 *puVar9;
  float fVar10;
  VECTOR_3D local_c0;
  VECTOR_3D local_b4;
  ENTITY_LOADER local_a8;
  float local_54;
  float fStack_50;
  float fStack_4c;
  char *local_48;
  int local_44;
  char local_40 [39];
  undefined4 uStack_19;
  undefined1 auStack_14 [4];
  undefined1 local_10;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)(local_a8.lodRanges + 1);
  local_48 = param_5;
  if (param_4 < 1) {
    sVar3 = find_empty_seqno(this->base);
    param_4 = (int)sVar3;
  }
  if (param_5 == (char *)0x0) {
    sprintf(local_40,"%.8s%d_%s",(short)&this->cfg,param_4,this->label);
    local_48 = local_40;
  }
  memset((short)&local_a8,0,0x54);
  local_a8.entObj = create_obj((_OBJ76 *)0x0,".\\fun3d\\GameObjectClass.cpp");
  *(int *)&(local_a8.entObj)->id = (int)this->cfg;
  *(undefined4 *)((int)&(local_a8.entObj)->id + 4) = *(undefined4 *)((int)&this->cfg + 4);
  pMVar8 = &(local_a8.entObj)->transform;
  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
    pMVar8->right_x = param_1->right_x;
    param_1 = (MAT_3D *)&param_1->right_y;
    pMVar8 = (MAT_3D *)&pMVar8->right_y;
  }
  (local_a8.entObj)->flags = param_2 << 0x10;
  if (param_3 != 0) {
    (local_a8.entObj)->flags = (local_a8.entObj)->flags | 0x10;
  }
  ClassCreate(local_a8.entObj,this->class_id);
  switch((local_a8.entObj)->class_id) {
  case CLASS_ID_HELICOPTER:
  case CLASS_ID_POWERUP:
  case CLASS_ID_PERSON:
  case CLASS_ID_VEHICLE:
    strncpy((char *)((int)&uStack_19 + 1),(char *)&this->base,8);
    local_10 = 0;
    puVar2 = &uStack_19;
    do {
      puVar9 = puVar2;
      puVar2 = (undefined4 *)((int)puVar9 + 1);
    } while (*(char *)((int)puVar9 + 1) != '\0');
    *(undefined4 *)((int)puVar9 + 1) = 0x6664762e;
    *(undefined1 *)((int)puVar9 + 5) = 0;
    local_44 = LoadVehicle((ObjectType *)0x0,&local_a8,(char *)((int)&uStack_19 + 1));
    get_obj_bounding_box(local_a8.entObj,&(this->bBox).min,&(this->bBox).max);
    pVVar4 = &local_b4;
    break;
  case CLASS_ID_STRUCTURE1:
  case CLASS_ID_SIGN:
  case CLASS_ID_SCRAP:
  case CLASS_ID_BRIDGE:
  case CLASS_ID_STRUCTURE2:
  case CLASS_ID_SPINNER:
    strncpy((char *)((int)&uStack_19 + 1),(char *)&this->base,8);
    local_10 = 0;
    puVar2 = &uStack_19;
    do {
      puVar9 = puVar2;
      puVar2 = (undefined4 *)((int)puVar9 + 1);
    } while (*(char *)((int)puVar9 + 1) != '\0');
    *(undefined4 *)((int)puVar9 + 1) = 0x6664732e;
    *(undefined1 *)((int)puVar9 + 5) = 0;
    local_44 = LoadStructure((StructObjectType *)0x0,&local_a8,(char *)((int)&uStack_19 + 1));
    get_obj_bounding_box(local_a8.entObj,&(this->bBox).min,&(this->bBox).max);
    pVVar4 = &local_c0;
    break;
  default:
    local_44 = 0;
    goto LAB_00498f69;
  }
  pVVar4 = get_obj_geometric_center(pVVar4,local_a8.entObj);
  local_54 = pVVar4->x;
  fStack_50 = pVVar4->y;
  fStack_4c = pVVar4->z;
  VVar1 = *pVVar4;
  (this->bSphere).origin.x = local_54;
  (this->bSphere).origin.y = fStack_50;
  (this->bSphere).origin.z = fStack_4c;
  fVar10 = get_obj_radius(local_a8.entObj,VVar1);
  (this->bSphere).radius = fVar10;
LAB_00498f69:
  if (local_44 == 0) {
    TraceError("GameObject \"%s\" could not load \"%s\"\n");
  }
  if (local_a8.clsnPlanesFound == 0) {
    pCVar5 = (CLSN_BOXES *)0x0;
  }
  else {
    pCVar5 = GetClsnPlanes(&local_a8.clsnPlanes);
  }
  ptVar6 = add_entity(local_a8.entObj,(short)param_4,pCVar5,
                      (float *)(-(uint)(local_a8.lodRangesFound != 0) & (uint)local_a8.lodRanges));
  ClassFirstFunctions();
  if (ptVar6->obj76 == (_OBJ76 *)0x0) {
    this_00 = (GameObject *)0x0;
  }
  else {
    this_00 = ptVar6->obj76->gameObj;
  }
  GameObject::SetLabel(this_00,local_48);
  return this_00;
}

/*
 * Entry: 00499007
 * Name: GameObjectClass::InitBoundingData
 * Namespace: GameObjectClass
 * Signature: void InitBoundingData(GameObjectClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall GameObjectClass::InitBoundingData(GameObjectClass *this)

{
  VECTOR_3D VVar1;
  undefined4 *puVar2;
  VECTOR_3D *pVVar3;
  undefined4 *puVar4;
  float fVar5;
  VECTOR_3D local_94;
  VECTOR_3D local_88;
  ENTITY_LOADER local_7c;
  float local_28;
  float fStack_24;
  float fStack_20;
  undefined1 local_1c [4];
  char local_18 [4];
  undefined1 auStack_14 [4];
  undefined1 local_10;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_7c.entObj = create_obj((_OBJ76 *)0x0,".\\fun3d\\GameObjectClass.cpp");
  *(int *)&(local_7c.entObj)->id = (int)this->cfg;
  *(undefined4 *)((int)&(local_7c.entObj)->id + 4) = *(undefined4 *)((int)&this->cfg + 4);
  ClassCreate(local_7c.entObj,this->class_id);
  switch((local_7c.entObj)->class_id) {
  case CLASS_ID_HELICOPTER:
  case CLASS_ID_POWERUP:
  case CLASS_ID_PERSON:
  case CLASS_ID_VEHICLE:
    strncpy(local_18,(char *)&this->base,8);
    local_10 = 0;
    puVar2 = (undefined4 *)(local_1c + 3);
    do {
      puVar4 = puVar2;
      puVar2 = (undefined4 *)((int)puVar4 + 1);
    } while (*(char *)((int)puVar4 + 1) != '\0');
    *(undefined4 *)((int)puVar4 + 1) = 0x6664762e;
    *(undefined1 *)((int)puVar4 + 5) = 0;
    local_1c = (undefined1  [4])LoadVehicle((ObjectType *)0x0,&local_7c,local_18);
    get_obj_bounding_box(local_7c.entObj,&(this->bBox).min,&(this->bBox).max);
    pVVar3 = &local_88;
    break;
  case CLASS_ID_STRUCTURE1:
  case CLASS_ID_SIGN:
  case CLASS_ID_SCRAP:
  case CLASS_ID_BRIDGE:
  case CLASS_ID_STRUCTURE2:
  case CLASS_ID_SPINNER:
    strncpy(local_18,(char *)&this->base,8);
    local_10 = 0;
    puVar2 = (undefined4 *)(local_1c + 3);
    do {
      puVar4 = puVar2;
      puVar2 = (undefined4 *)((int)puVar4 + 1);
    } while (*(char *)((int)puVar4 + 1) != '\0');
    *(undefined4 *)((int)puVar4 + 1) = 0x6664732e;
    *(undefined1 *)((int)puVar4 + 5) = 0;
    local_1c = (undefined1  [4])LoadStructure((StructObjectType *)0x0,&local_7c,local_18);
    get_obj_bounding_box(local_7c.entObj,&(this->bBox).min,&(this->bBox).max);
    pVVar3 = &local_94;
    break;
  default:
    local_1c = (undefined1  [4])0x0;
    goto LAB_00499160;
  }
  pVVar3 = get_obj_geometric_center(pVVar3,local_7c.entObj);
  local_28 = pVVar3->x;
  fStack_24 = pVVar3->y;
  fStack_20 = pVVar3->z;
  VVar1 = *pVVar3;
  (this->bSphere).origin.x = local_28;
  (this->bSphere).origin.y = fStack_24;
  (this->bSphere).origin.z = fStack_20;
  fVar5 = get_obj_radius(local_7c.entObj,VVar1);
  (this->bSphere).radius = fVar5;
LAB_00499160:
  if (local_1c == (undefined1  [4])0x0) {
    TraceError("GameObject \"%s\" could not load \"%s\"\n");
  }
  ClassNoFirstFunctions();
  remove_obj(local_7c.entObj,".\\fun3d\\GameObjectClass.cpp");
  return;
}

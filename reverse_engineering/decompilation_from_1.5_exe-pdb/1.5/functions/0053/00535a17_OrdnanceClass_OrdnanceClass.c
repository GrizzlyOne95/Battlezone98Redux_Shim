/*
 * Entry: 00535a17
 * Name: OrdnanceClass::OrdnanceClass
 * Namespace: OrdnanceClass
 * Signature: OrdnanceClass * OrdnanceClass(OrdnanceClass * this, OrdnanceClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

OrdnanceClass * __thiscall
OrdnanceClass::OrdnanceClass(OrdnanceClass *this,OrdnanceClass *param_1,long64 param_2)

{
  OrdnanceClass *pOVar1;
  undefined4 *puVar2;
  bool bVar3;
  ushort uVar4;
  _OBJ76 *p_Var5;
  tagENTITY *ptVar6;
  ExplosionClass *pEVar7;
  int iVar8;
  ushort uVar9;
  uint unaff_EBX;
  uint unaff_ESI;
  MAT_3D *pMVar10;
  uint unaff_EDI;
  undefined4 *puVar11;
  MAT_3D *pMVar12;
  float fVar13;
  uint in_stack_00000008;
  OrdnanceClass *local_44;
  float local_40;
  float local_3c;
  float local_38;
  uint local_34;
  float local_30;
  OrdnanceClass *local_2c;
  int local_28;
  int local_24;
  ParameterDB local_20;
  byte local_19;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_2c = param_1;
  this->_padding_ = (int)&_vftable_;
  this->proto = param_1;
  local_44 = this;
  std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::push_back(&classList,&local_44);
  this->sig = param_1->sig;
  this->label = param_1->label;
  *(uint *)&this->cfg = in_stack_00000008 & 0x7f7f7f7f;
  *(uint *)((int)&this->cfg + 4) = (uint)param_2 & 0x7f7f7f7f;
  strncpy(this->odf,(char *)&this->cfg,8);
  this->odf[8] = '\0';
  puVar2 = (undefined4 *)((int)&this->cfg + 7);
  do {
    puVar11 = puVar2;
    puVar2 = (undefined4 *)((int)puVar11 + 1);
  } while (*(char *)((int)puVar11 + 1) != '\0');
  *(undefined4 *)((int)puVar11 + 1) = 0x66646f2e;
  *(undefined1 *)((int)puVar11 + 5) = 0;
  ParameterDB::ParameterDB(&local_20,this->odf);
  p_Var5 = create_obj((_OBJ76 *)0x0,".\\fun3d\\OrdnanceClass.cpp");
  this->freeOrd = p_Var5;
  p_Var5 = create_obj((_OBJ76 *)0x0,".\\fun3d\\OrdnanceClass.cpp");
  this->ord = p_Var5;
  p_Var5->flags = 0;
  pMVar10 = &Identity_Matrix;
  pMVar12 = &this->ord->transform;
  for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
    pMVar12->right_x = pMVar10->right_x;
    pMVar10 = (MAT_3D *)&pMVar10->right_y;
    pMVar12 = (MAT_3D *)&pMVar12->right_y;
  }
  this->ord->geom = (_GEOMETRY *)0x0;
  this->ord->class_id = CLASS_ID_ORDNANCE;
  ParameterDB::Get(&local_20,0xd59a9357,0x6f31d8a1,local_18,0x10,(char *)0x0);
  if (local_18[0] != '\0') {
    iVar8 = GeoCache_AddRep(this->ord,local_18,0,0);
    if (iVar8 == 0) {
      TraceWarning("Ordnance \"%s\" could not add geometry \"%s\"\n");
    }
    p_Var5 = this->ord;
    get_obj_bounding_box(p_Var5,&(p_Var5->bBox).min,&(p_Var5->bBox).max);
    p_Var5 = this->ord;
    (p_Var5->bSphere).origin.x = ((p_Var5->bBox).max.x + (p_Var5->bBox).min.x) * 0.5;
    p_Var5 = this->ord;
    (p_Var5->bSphere).origin.y = ((p_Var5->bBox).max.y + (p_Var5->bBox).min.y) * 0.5;
    p_Var5 = this->ord;
    (p_Var5->bSphere).origin.z = ((p_Var5->bBox).max.z + (p_Var5->bBox).min.z) * 0.5;
    fVar13 = get_obj_radius(this->ord,(this->ord->bSphere).origin);
    (this->ord->bSphere).radius = fVar13;
  }
  p_Var5 = create_obj((_OBJ76 *)0x0,".\\fun3d\\OrdnanceClass.cpp");
  *(int *)&p_Var5->id = (int)this->cfg;
  *(undefined4 *)((int)&p_Var5->id + 4) = *(undefined4 *)((int)&this->cfg + 4);
  p_Var5->flags = 0x101;
  p_Var5->class_id = CLASS_ID_ORDNANCE;
  p_Var5->class_ptr = (void *)0x0;
  p_Var5->sibling = (_OBJ76 *)0x0;
  p_Var5->child = (_OBJ76 *)0x0;
  ptVar6 = add_entity(p_Var5,0,(CLSN_BOXES *)0x0,(float *)0x0);
  this->ent = ptVar6;
  ParameterDB::Get(&local_20,0xd59a9357,0x5acba4c4,(long64 *)&local_28,(ulonglong)unaff_EDI << 0x20)
  ;
  if (local_28 == 0 && local_24 == 0) {
    pEVar7 = local_2c->xplGround;
  }
  else {
    pEVar7 = ExplosionClass::Find(CONCAT44(local_24,local_28));
  }
  pOVar1 = local_2c;
  this->xplGround = pEVar7;
  ParameterDB::Get(&local_20,0xd59a9357,0x1564c7e9,(long64 *)&local_28,(ulonglong)unaff_ESI << 0x20)
  ;
  if (local_28 == 0 && local_24 == 0) {
    pEVar7 = pOVar1->xplGround;
  }
  else {
    pEVar7 = ExplosionClass::Find(CONCAT44(local_24,local_28));
  }
  this->xplVehicle = pEVar7;
  ParameterDB::Get(&local_20,0xd59a9357,0x427beb6f,(long64 *)&local_28,(ulonglong)unaff_EBX << 0x20)
  ;
  if (local_28 == 0 && local_24 == 0) {
    pEVar7 = pOVar1->xplGround;
  }
  else {
    pEVar7 = ExplosionClass::Find(CONCAT44(local_24,local_28));
  }
  this->xplBuilding = pEVar7;
  ParameterDB::Get(&local_20,0xd59a9357,0x7c7c544b,&this->lifeSpan,pOVar1->lifeSpan);
  ParameterDB::Get(&local_20,0xd59a9357,0xcafe92d0,&this->shotSpeed,pOVar1->shotSpeed);
  ParameterDB::Get(&local_20,0xd59a9357,0xe4af0ab6,&this->ammoCost,pOVar1->ammoCost);
  this->damageValue = pOVar1->damageValue;
  this->damageTypes = pOVar1->damageTypes;
  local_19 = ParameterDB::Get(&local_20,0xd59a9357,0x52fd4a53,&local_30,0.0);
  bVar3 = ParameterDB::Get(&local_20,0xd59a9357,0x38720d72,&local_38,0.0);
  local_19 = local_19 | bVar3;
  bVar3 = ParameterDB::Get(&local_20,0xd59a9357,0x7c8a1300,&local_40,0.0);
  local_19 = bVar3 | local_19;
  bVar3 = ParameterDB::Get(&local_20,0xd59a9357,0x5be2a777,&local_3c,0.0);
  if (bVar3 || local_19 != 0) {
    this->damageValue = local_38 + local_30 + local_40 + local_3c;
    if (local_40 == 0.0) {
      uVar9 = 0;
    }
    else {
      uVar9 = 2;
    }
    if (local_30 == 0.0) {
      local_2c = (OrdnanceClass *)0x0;
    }
    else {
      local_2c = (OrdnanceClass *)0x4;
    }
    if (local_38 == 0.0) {
      uVar4 = 0;
    }
    else {
      uVar4 = 8;
    }
    this->damageTypes = local_3c != 0.0 | uVar9 | (ushort)local_2c | uVar4;
  }
  ParameterDB::Get(&local_20,0xd59a9357,0x541f3a64,this->shotSound,0x10,pOVar1->shotSound);
  local_34 = (uint)pOVar1->notifyRemote;
  ParameterDB::Get(&local_20,0xd59a9357,0x92dacba,(long *)&local_34,local_34);
  this->notifyRemote = local_34 != 0;
  ParameterDB::~ParameterDB(&local_20);
  return this;
}

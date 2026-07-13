/*
 * Entry: 00534aac
 * Name: Ordnance::Init
 * Namespace: Ordnance
 * Signature: void Init(Ordnance * this, MAT_3D * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall Ordnance::Init(Ordnance *this,MAT_3D *param_1,_OBJ76 *param_2)

{
  undefined1 *puVar1;
  _OBJ76 *p_Var2;
  OrdnanceClass *pOVar3;
  MAT_3D MVar4;
  _Node *p_Var5;
  bool bVar6;
  ushort uVar7;
  RMAT *pRVar8;
  MAT_3D *pMVar9;
  _gas_object *p_Var10;
  int iVar11;
  float *pfVar12;
  undefined4 unaff_EDI;
  MAT_3D *pMVar13;
  float fVar14;
  float fStack_104;
  undefined1 in_stack_ffffff00 [32];
  undefined4 in_stack_ffffff20;
  undefined4 in_stack_ffffff24;
  undefined4 in_stack_ffffff28;
  undefined4 in_stack_ffffff2c;
  undefined4 in_stack_ffffff30;
  undefined4 in_stack_ffffff34;
  undefined2 uVar15;
  undefined2 uVar16;
  MAT_3D local_b8;
  GAS_PREP_INFO local_78;
  pair<std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::iterator,bool>
  local_5c;
  _Const_iterator<1> local_50;
  float local_48 [5];
  GAS_CTRL local_34;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_50._Ptr = (_Node *)param_2;
  if (param_2 == (_OBJ76 *)0x0) {
    this->obj->flags = 0;
  }
  else {
    this->obj->flags = param_2->flags & 0xf0000;
  }
  pMVar9 = &this->obj->transform;
  for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
    pMVar9->right_x = param_1->right_x;
    param_1 = (MAT_3D *)&param_1->right_y;
    pMVar9 = (MAT_3D *)&pMVar9->right_y;
  }
  uVar15 = 0x4af8;
  uVar16 = 0x53;
  iVar11 = Net_IsNetGame();
  if (iVar11 != 0) {
    pMVar9 = &this->obj->transform;
    pfVar12 = &fStack_104;
    for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
      *pfVar12 = pMVar9->right_x;
      pMVar9 = (MAT_3D *)&pMVar9->right_y;
      pfVar12 = pfVar12 + 1;
    }
    MVar4.front_z = (float)in_stack_ffffff20;
    MVar4.right_x = (float)in_stack_ffffff00._0_4_;
    MVar4.right_y = (float)in_stack_ffffff00._4_4_;
    MVar4.right_z = (float)in_stack_ffffff00._8_4_;
    MVar4.up_x = (float)in_stack_ffffff00._12_4_;
    MVar4.up_y = (float)in_stack_ffffff00._16_4_;
    MVar4.up_z = (float)in_stack_ffffff00._20_4_;
    MVar4.front_x = (float)in_stack_ffffff00._24_4_;
    MVar4.front_y = (float)in_stack_ffffff00._28_4_;
    MVar4._36_4_ = in_stack_ffffff24;
    MVar4.posit_x._0_4_ = in_stack_ffffff28;
    MVar4.posit_x._4_4_ = in_stack_ffffff2c;
    MVar4.posit_y._0_4_ = in_stack_ffffff30;
    MVar4.posit_y._4_4_ = in_stack_ffffff34;
    MVar4.posit_z._0_2_ = uVar15;
    MVar4.posit_z._2_2_ = uVar16;
    MVar4.posit_z._4_4_ = unaff_EDI;
    pRVar8 = NetUtil_ReduceMatNoRoll((RMAT *)&local_5c,MVar4);
    pMVar9 = NetUtil_ExpandMatNoRoll(&local_b8,(RMAT)*&pRVar8->buf);
    pfVar12 = local_48;
    for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
      *pfVar12 = pMVar9->right_x;
      pMVar9 = (MAT_3D *)&pMVar9->right_y;
      pfVar12 = pfVar12 + 1;
    }
    pfVar12 = local_48;
    pMVar9 = &this->obj->transform;
    for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
      pMVar9->right_x = *pfVar12;
      pfVar12 = pfVar12 + 1;
      pMVar9 = (MAT_3D *)&pMVar9->right_y;
    }
  }
  add_obj_to_tree(this->obj,this->ordnanceClass->ent->obj76);
  p_Var5 = local_50._Ptr;
  (this->damage).damager = (_OBJ76 *)0x0;
  (this->damage).dmg_source = (_OBJ76 *)0x0;
  *(undefined4 *)&(this->damage).field_0x8 = 0;
  (this->damage).dmg_value = 0.0;
  p_Var2 = this->obj;
  (this->damage).dmg_source = p_Var2;
  (this->damage).damager = (_OBJ76 *)local_50._Ptr;
  puVar1 = &(this->damage).field_0x8;
  *(ushort *)puVar1 =
       *(ushort *)puVar1 ^
       (*(short *)((int)&p_Var2->flags + 2) << 6 ^ *(ushort *)&(this->damage).field_0x8) & 0x3c0;
  uVar7 = *(ushort *)&(this->damage).field_0x8;
  if ((_OBJ76 *)local_50._Ptr != (_OBJ76 *)0x0) {
    *(ushort *)&(this->damage).field_0x8 =
         ((ushort)((*(ulong *)((int)local_50._Ptr + 0x14) & 0x30) != 0) << 4 ^ uVar7) & 0x10 ^ uVar7
    ;
    if (*(void **)((int)local_50._Ptr + 0xb4) != (void *)0x0) {
      bVar6 = DistributedObject::IsRemote
                        ((DistributedObject *)((int)*(void **)((int)local_50._Ptr + 0xb4) + 0x20));
      *(ushort *)&(this->damage).field_0x8 =
           (ushort)bVar6 << 5 | *(ushort *)&(this->damage).field_0x8 & 0xffdf;
    }
  }
  pOVar3 = this->ordnanceClass;
  puVar1 = &(this->damage).field_0x8;
  *(ushort *)puVar1 =
       *(ushort *)puVar1 ^ (pOVar3->damageTypes ^ *(ushort *)&(this->damage).field_0x8) & 0xf;
  (this->damage).dmg_value = pOVar3->damageValue;
  this->owner = (_OBJ76 *)p_Var5;
  if ((_OBJ76 *)p_Var5 == (_OBJ76 *)0x0) {
    this->ownerHandle = 0;
  }
  else {
    this->ownerHandle = (int)*(_OBJHANDLE *)&p_Var5->_Next;
  }
  i_got_dibs_on_obj((_OBJ76 *)p_Var5,pOVar3->odf);
  InitEuler(&this->euler);
  fVar14 = this->ordnanceClass->lifeSpan;
  this->go = (_gas_object *)0x0;
  this->lifeTimer = fVar14;
  if (this->ordnanceClass->shotSound[0] != '\0') {
    InitGASCtrl(&local_34);
    local_34.flags = 0x1001;
    InitGASPrep(&local_78);
    local_78.loopMode = 1;
    p_Var10 = StartGASEvent(this->ordnanceClass->shotSound,this->obj,&local_34,&local_78);
    this->go = p_Var10;
  }
  local_50._Ptr = (_Node *)this;
  std::list<Ordnance_*,std::allocator<Ordnance_*>_>::push_front
            (&ordnanceList,(Ordnance **)&local_50._Ptr);
  std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_50,(ordnanceList._Myhead)->_Next,&ordnanceList);
  *(int *)&this->me = local_50._padding_;
  *(_Node **)&(this->me).field_0x4 = local_50._Ptr;
  iVar11 = Net_IsNetGame();
  if (iVar11 != 0) {
    uVar7 = Net_GetMyPlayerID();
    this->source = uVar7;
    g_next_ordid = g_next_ordid + 1;
    this->ordid = g_next_ordid;
    local_50._padding_._0_2_ = this->source;
    local_50._padding_._2_2_ = this->ordid;
    this->bSend = 1;
    local_50._Ptr = (_Node *)this;
    std::
    _Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
    ::insert((_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
              *)&netOrdnanceMap,&local_5c,
             (pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*> *)&local_50);
  }
  pMVar9 = &this->obj->transform;
  pMVar13 = &this->initMat;
  for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
    pMVar13->right_x = pMVar9->right_x;
    pMVar9 = (MAT_3D *)&pMVar9->right_y;
    pMVar13 = (MAT_3D *)&pMVar13->right_y;
  }
  fVar14 = Get_Time();
  this->initTime = fVar14;
  return;
}

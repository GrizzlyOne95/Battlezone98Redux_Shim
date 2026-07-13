/*
 * Entry: 00499e42
 * Name: GameObjectClass::GameObjectClass
 * Namespace: GameObjectClass
 * Signature: GameObjectClass * GameObjectClass(GameObjectClass * this, GameObjectClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Type propagation algorithm not settling */

GameObjectClass * __thiscall
GameObjectClass::GameObjectClass(GameObjectClass *this,GameObjectClass *param_1,long64 param_2)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  GameObjectClass *pGVar4;
  WeaponClass *pWVar5;
  long lVar6;
  char *pcVar7;
  void *pvVar8;
  char *pcVar9;
  undefined4 unaff_EBX;
  undefined4 unaff_ESI;
  BBOX *pBVar10;
  undefined4 unaff_EDI;
  BBOX *pBVar11;
  uint in_stack_00000008;
  GameObjectClass *pGVar12;
  undefined8 local_60;
  WeaponClass **local_58;
  undefined8 local_54;
  ParameterDB local_4c;
  char local_48 [32];
  undefined4 local_28;
  undefined4 uStack_24;
  int iStack_20;
  GameObjectClass *pGStack_1c;
  undefined4 local_18;
  undefined4 uStack_14;
  int local_10;
  GameObjectClass *local_c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  pGVar12 = param_1;
  Attachable::Attachable((Attachable *)this);
  this->_padding_ = (int)&_vftable_;
  this->proto = param_1;
  local_54._4_4_ = this;
  std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::push_back
            (&classList,(GameObjectClass **)((int)&local_54 + 4));
  Attachable::InitAttachments((Attachable *)this,gameObjectClass.attachCount);
  this->sig = param_1->sig;
  this->label = param_1->label;
  this->class_id = param_1->class_id;
  pcVar7 = this->odf;
  *(uint *)&this->cfg = in_stack_00000008 & 0x7f7f7f7f;
  *(uint *)((int)&this->cfg + 4) = (uint)param_2 & 0x7f7f7f7f;
  sprintf(pcVar7,"%.8s.odf",&stack0x00000008);
  iVar3 = ItemExists(pcVar7);
  if (iVar3 == 0) {
    TraceError("Missing game object %s");
  }
  ParameterDB::ParameterDB(&local_4c,pcVar7);
  ParameterDB::Get(&local_4c,0xd3dd9cec,0x794b13b,&this->base,
                   CONCAT44(unaff_EDI,*(undefined4 *)((int)&this->cfg + 4)));
  ParameterDB::Get(&local_4c,0xd3dd9cec,0x9de6f3f3,&this->scrapCost,param_1->scrapCost);
  ParameterDB::Get(&local_4c,0xd3dd9cec,0x262c569b,&this->scrapValue,param_1->scrapValue);
  ParameterDB::Get(&local_4c,0xd3dd9cec,0xcdb7d0f4,&this->pilotCost,param_1->pilotCost);
  ParameterDB::Get(&local_4c,0xd3dd9cec,0xed76d3a,&this->buildTime,param_1->buildTime);
  ParameterDB::Get(&local_4c,0xd3dd9cec,0x19971f1b,&this->maxHealth,param_1->maxHealth);
  ParameterDB::Get(&local_4c,0xd3dd9cec,0x21c4ff9b,&this->maxAmmo,param_1->maxAmmo);
  ParameterDB::Get(&local_4c,0xd3dd9cec,0x45a8bc04,this->unitName,0x20,param_1->unitName);
  if (this->unitName[0] == '\0') {
    this->unitNameIndex = 0;
  }
  else {
    iVar3 = GetSpriteIndex(this->unitName);
    this->unitNameIndex = iVar3;
  }
  ParameterDB::Get(&local_4c,0xd3dd9cec,0x98d7239c,this->aiName,0x20,param_1->aiName);
  ParameterDB::Get(&local_4c,0xd3dd9cec,0x48ad2aea,this->aiName2,0x20,param_1->aiName2);
  ParameterDB::Get(&local_4c,0xd3dd9cec,0xba10bbdd,&this->weaponMask,param_1->weaponMask);
  ParameterDB::Get(&local_4c,0xd3dd9cec,0x20844ad,&this->collisionRadius,param_1->collisionRadius);
  bVar2 = ParameterDB::Get(&local_4c,0xd3dd9cec,0x3957bd3a,local_48,0x20,(char *)0x0);
  if (bVar2) {
LAB_0049a06d:
    iVar3 = tolower((int)local_48[0]);
    this->nation = (char)iVar3;
  }
  else {
    iVar3 = _stricmp(this->odf,"player.odf");
    if (iVar3 != 0) {
      local_48[0] = this->odf[0];
      goto LAB_0049a06d;
    }
    this->nation = 'a';
  }
  pGVar4 = (GameObjectClass *)0x0;
  if (this->pilotCost < 1) {
    this->pilotClass = (GameObjectClass *)0x0;
  }
  else {
    local_60._0_4_ = CONCAT31(0x697073,this->nation);
    local_60._4_4_ = 0x6f6c;
    sprintf((char *)&local_18,"%.8s.odf",&local_60);
    bVar2 = Net::IsNetGame();
    if ((bVar2) && (Net::bNations == false)) {
LAB_0049a0d3:
      if (this->nation != 'c') {
        local_60._0_4_ = CONCAT31(local_60._1_3_,0x61);
        if (this->nation != 's') goto LAB_0049a0e9;
      }
      local_60._0_4_ = CONCAT31(local_60._1_3_,0x73);
    }
    else {
      iVar3 = ItemExists((char *)&local_18);
      if (iVar3 == 0) goto LAB_0049a0d3;
    }
LAB_0049a0e9:
    ParameterDB::Get(&local_4c,0xd3dd9cec,0xde331a5a,&local_60,CONCAT44(unaff_ESI,local_60._4_4_));
    if ((int)local_60 == 0 && local_60._4_4_ == 0) {
      this->pilotClass = (GameObjectClass *)0x0;
    }
    else {
      pGVar4 = Find(CONCAT44(local_60._4_4_,(int)local_60));
      this->pilotClass = pGVar4;
    }
    local_54._0_4_ = CONCAT31(0x737573,this->nation);
    local_54._4_4_ = (GameObjectClass *)0x7265;
    sprintf((char *)&local_18,"%.8s.odf",&local_54);
    bVar2 = Net::IsNetGame();
    if ((bVar2) && (Net::bNations == false)) {
LAB_0049a172:
      if (this->nation != 'c') {
        local_54._0_4_ = CONCAT31(local_54._1_3_,0x61);
        if (this->nation != 's') goto LAB_0049a188;
      }
      local_54._0_4_ = CONCAT31(local_54._1_3_,0x73);
    }
    else {
      iVar3 = ItemExists((char *)&local_18);
      if (iVar3 == 0) goto LAB_0049a172;
    }
LAB_0049a188:
    ParameterDB::Get(&local_4c,0xd3dd9cec,0x4eaf15b9,&local_54,CONCAT44(unaff_EBX,local_54._4_4_));
    if ((int)local_54 == 0 && local_54._4_4_ == (GameObjectClass *)0x0) {
      this->userClass = (GameObjectClass *)0x0;
      goto LAB_0049a1cc;
    }
    pGVar4 = Find(CONCAT44(local_54._4_4_,(int)local_54));
  }
  this->userClass = pGVar4;
LAB_0049a1cc:
  ParameterDB::Get(&local_4c,0xd3dd9cec,0x21c2c4f0,&this->imageSignature,param_1->imageSignature);
  ParameterDB::Get(&local_4c,0xd3dd9cec,0xf52cb94f,&this->radarSignature,param_1->radarSignature);
  ParameterDB::Get(&local_4c,0xd3dd9cec,0xb1c56677,&this->heatSignature,param_1->heatSignature);
  local_54._4_4_ = (GameObjectClass *)0x0;
  local_58 = this->weaponClass;
  do {
    local_60._4_4_ = (uint)(byte)(local_54._4_1_ + 0x31);
    ParameterDB::Get(&local_4c,0xd3dd9cec,(local_60._4_4_ ^ 0x157ba160) * 0x1000193,
                     (char *)(local_58 + -5),4,(char *)0x0);
    ParameterDB::Get(&local_4c,0xd3dd9cec,(local_60._4_4_ ^ 0xfbf47dba) * 0x1000193,
                     (long64 *)&local_10,ZEXT48(pGVar12) << 0x20);
    if (local_10 == 0 && local_c == (GameObjectClass *)0x0) goto LAB_0049a2e3;
    pGVar12 = local_c;
    pWVar5 = WeaponClass::Find(CONCAT44(local_c,local_10));
    *local_58 = pWVar5;
    if (pWVar5 != (WeaponClass *)0x0) {
      pGVar12 = (GameObjectClass *)0x49a2a4;
      bVar2 = Net::IsNetGame();
      if (bVar2) {
        if ((Net::bSniper == false) && ((*local_58)->sig == 0x534e4950)) {
LAB_0049a2e3:
          *local_58 = (WeaponClass *)0x0;
        }
        else if (Net::bSplint == false) {
          pGVar12 = (GameObjectClass *)0x49a2cd;
          bVar2 = Net::IsDeathMatch();
          if (((!bVar2) && (local_10 == 0x6c707367)) &&
             (local_c == (GameObjectClass *)((int)&AllStrips[0x423a]._padding_ + 1)))
          goto LAB_0049a2e3;
        }
      }
    }
    local_54._4_4_ = (GameObjectClass *)((int)local_54._4_4_ + 1);
    local_58 = local_58 + 1;
    if (4 < (int)local_54._4_4_) {
      pBVar10 = &param_1->bBox;
      pBVar11 = &this->bBox;
      for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
        (pBVar11->min).x = (pBVar10->min).x;
        pBVar10 = (BBOX *)&(pBVar10->min).y;
        pBVar11 = (BBOX *)&(pBVar11->min).y;
      }
      (this->bSphere).origin.x = (pGVar12->bSphere).origin.x;
      (this->bSphere).origin.y = (pGVar12->bSphere).origin.y;
      (this->bSphere).origin.z = (pGVar12->bSphere).origin.z;
      (this->bSphere).radius = (pGVar12->bSphere).radius;
      this->categoryMin = pGVar12->categoryMin;
      this->categoryMax = pGVar12->categoryMax;
      sprintf((char *)&local_28,"%.8s.inf",&stack0x00000008);
      iVar3 = ItemExists((char *)&local_28);
      if (iVar3 == 0) {
        sprintf((char *)&local_18,"%.8s.inf",&this->base);
        iVar3 = ItemExists((char *)&local_18);
        if (iVar3 != 0) {
          local_28 = local_18;
          uStack_24 = uStack_14;
          iStack_20 = local_10;
          pGStack_1c = local_c;
        }
      }
      lVar6 = GetItemSize((char *)&local_28);
      if (lVar6 < 1) {
        pcVar7 = (char *)&local_28;
        do {
          cVar1 = *pcVar7;
          pcVar7 = pcVar7 + 1;
        } while (cVar1 != '\0');
        pcVar9 = operator_new__((uint)(pcVar7 + (1 - ((int)&local_28 + 1))));
        this->infoText = pcVar9;
        pcVar7 = (char *)&local_28;
        do {
          cVar1 = *pcVar7;
          pcVar7 = pcVar7 + 1;
          *pcVar9 = cVar1;
          pcVar9 = pcVar9 + 1;
        } while (cVar1 != '\0');
      }
      else {
        pcVar7 = operator_new__(lVar6 + 1);
        this->infoText = pcVar7;
        pvVar8 = UseItem((char *)&local_28);
        memcpy(this->infoText,pvVar8,lVar6);
        this->infoText[lVar6] = '\0';
        UnlockItem((char *)&local_28);
      }
      if ((D3IniFlags & 0x8000U) != 0) {
        InitBoundingData(this);
      }
      ParameterDB::~ParameterDB(&local_4c);
      return this;
    }
  } while( true );
}

/*
 * Entry: 004c3f32
 * Name: InitBuildItem
 * Namespace: Global
 * Signature: void InitBuildItem(BuildItem * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl InitBuildItem(BuildItem *param_1,long64 param_2)

{
  char *pcVar1;
  bool bVar2;
  int iVar3;
  long lVar4;
  BuildItem *pBVar5;
  uint uVar6;
  GameObjectClass *pGVar7;
  undefined4 unaff_ESI;
  uint unaff_EDI;
  undefined4 in_stack_00000008;
  long64 *plVar8;
  undefined4 uVar9;
  char local_4c [4];
  undefined8 local_48;
  ParameterDB local_40;
  ParameterDB local_3c;
  char local_38 [16];
  char local_28 [16];
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  sprintf(local_28,"%.8s.odf",&stack0x00000008);
  ParameterDB::ParameterDB(&local_40,local_28);
  bVar2 = ParameterDB::Get(&local_40,0xe4350540,0xcf7a27e8,param_1->name,0x10,(char *)0x0);
  pcVar1 = param_1->name;
  if (bVar2) {
    if (*pcVar1 == '\0') {
      iVar3 = 0;
    }
    else {
      iVar3 = GetSpriteIndex(pcVar1);
    }
    param_1->index = iVar3;
    if (param_1->parent == (BuildItem *)0x0) {
      lVar4 = 0;
    }
    else {
      lVar4 = param_1->parent->team;
    }
    ParameterDB::Get(&local_40,0xe4350540,0xcb5fbcaa,&param_1->team,lVar4);
    pBVar5 = calloc(10,0x24);
    param_1->menu = pBVar5;
    iVar3 = 0;
    param_1->item = (GameObjectClass *)0x0;
    local_3c.DB_file = (FileData *)0x0;
    do {
      iVar3 = iVar3 + 1;
      *(BuildItem **)(param_1->menu->name + (int)((local_3c.DB_file)->DB_name + -8)) = param_1;
      sprintf(local_4c,"%d",iVar3);
      uVar9 = 0;
      plVar8 = &local_48;
      uVar6 = Hash(local_4c,0xf1915444);
      ParameterDB::Get(&local_40,0xe4350540,uVar6,plVar8,CONCAT44(unaff_EDI,uVar9));
      if ((int)local_48 != 0 || local_48._4_4_ != 0) {
        unaff_EDI = local_48._4_4_;
        InitBuildItem((BuildItem *)((local_3c.DB_file)->DB_name + (int)(param_1->menu->name + -8)),
                      CONCAT44(unaff_ESI,local_48._4_4_));
      }
      local_3c.DB_file = (FileData *)&((local_3c.DB_file)->DB_map).field_0xc;
    } while ((int)local_3c.DB_file < 0x168);
  }
  else {
    bVar2 = ParameterDB::Get(&local_40,0xd3dd9cec,0x45a8bc04,pcVar1,0x10,(char *)0x0);
    if (!bVar2) {
      ParameterDB::Get(&local_40,0xd3dd9cec,0x92d04727,local_18,0x10,(char *)0x0);
      iVar3 = _stricmp(local_18,"wpnpower");
      if (iVar3 == 0) {
        ParameterDB::Get(&local_40,0x397a9ac1,0xfbf47dba,&local_48,(ulonglong)unaff_EDI << 0x20);
        sprintf(local_38,"%.8s.odf",&local_48);
        ParameterDB::ParameterDB(&local_3c,local_38);
        ParameterDB::Get(&local_3c,0xacda90ab,0xf429d8cf,param_1->name,0x10,(char *)0x0);
        ParameterDB::~ParameterDB(&local_3c);
      }
    }
    if (param_1->name == (char *)0x0) {
      iVar3 = 0;
    }
    else {
      iVar3 = GetSpriteIndex(param_1->name);
    }
    param_1->menu = (BuildItem *)0x0;
    param_1->index = iVar3;
    pGVar7 = GameObjectClass::Find(CONCAT44((undefined4)param_2,in_stack_00000008));
    param_1->item = pGVar7;
    param_1->team = param_1->parent->team;
  }
  ParameterDB::~ParameterDB(&local_40);
  return;
}

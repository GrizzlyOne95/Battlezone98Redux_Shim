/*
 * Entry: 0051a071
 * Name: RecurseBuildItem
 * Namespace: Global
 * Signature: void RecurseBuildItem(long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl RecurseBuildItem(long64 param_1)

{
  bool bVar1;
  int iVar2;
  GameObjectClass *pGVar3;
  undefined4 unaff_EBX;
  uint uVar4;
  long64 *plVar5;
  undefined4 uVar6;
  int local_40;
  ParameterDB local_3c;
  int local_38;
  int local_34;
  char local_30 [16];
  char local_20 [16];
  char local_10 [8];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  sprintf(local_20,"%.8s.odf",&param_1);
  iVar2 = ItemExists(local_20);
  if (iVar2 != 0) {
    ParameterDB::ParameterDB(&local_3c,local_20);
    bVar1 = ParameterDB::Get(&local_3c,0xd3dd9cec,0x92d04727,local_30,0x10,(char *)0x0);
    if (bVar1) {
      pGVar3 = GameObjectClass::Find(param_1);
      if (pGVar3 != (GameObjectClass *)0x0) {
        AddObjectClass(pGVar3,(GameObjectClass *)0x0);
      }
    }
    else {
      local_40 = 1;
      sprintf(local_10,"%d",1);
      uVar6 = 0;
      plVar5 = (long64 *)&local_38;
      uVar4 = 0xf1915444;
      local_38 = 0;
      local_34 = 0;
      Hash(local_10,0xf1915444);
      while( true ) {
        bVar1 = ParameterDB::Get(&local_3c,0xe4350540,uVar4,plVar5,CONCAT44(unaff_EBX,uVar6));
        if (!bVar1) break;
        if (local_38 != 0 || local_34 != 0) {
          RecurseBuildItem(CONCAT44(local_34,local_38));
        }
        local_40 = local_40 + 1;
        sprintf(local_10,"%d",local_40);
        unaff_EBX = 0;
        uVar6 = 0;
        plVar5 = (long64 *)0xf1915444;
        local_38 = 0;
        local_34 = 0;
        Hash((char *)0x51a174,0xf1915444);
      }
    }
    ParameterDB::~ParameterDB(&local_3c);
  }
  return;
}


void FUN_0041d220(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  TypeDescriptor *pTVar3;
  TypeDescriptor *pTVar4;
  undefined4 uVar5;
  int iVar6;
  undefined1 local_20 [4];
  undefined1 local_1c [8];
  undefined1 local_14 [4];
  int local_10;
  undefined1 local_c [4];
  undefined4 local_8;
  
  FUN_0041fc00(local_14);
  FUN_0041fc60(local_1c);
  while( true ) {
    cVar1 = FID_conflict_operator__(local_1c);
    if (cVar1 == '\0') break;
    local_8 = get();
    uVar5 = 0;
    pTVar4 = &TouchInputMasterButton::RTTI_Type_Descriptor;
    pTVar3 = &TouchInputButton::RTTI_Type_Descriptor;
    uVar2 = FUN_0041dd20(param_1,local_8,0);
    local_10 = __RTDynamicCast(uVar2,0,pTVar3,pTVar4,uVar5);
    if (local_10 != 0) {
      cVar1 = FUN_0041fc90();
      if (cVar1 == '\0') {
        FUN_0041fc00(local_c);
        FUN_0041fc60(local_20);
        while( true ) {
          cVar1 = FID_conflict_operator__(local_20);
          if (cVar1 == '\0') break;
          iVar6 = local_10;
          uVar2 = get(local_10);
          FUN_0041dd20(param_1,uVar2,iVar6);
          FUN_00422240();
        }
        FUN_0041b390();
      }
    }
    FUN_00422240();
  }
  return;
}


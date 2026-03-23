
undefined4 FUN_00430ab0(int param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 *puVar5;
  undefined4 uVar6;
  undefined1 *puVar7;
  undefined1 local_34 [12];
  undefined1 local_28 [12];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  int local_10;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  FUN_00428a90();
  if ((param_1 == 0) || (param_2 == 0)) {
    uVar2 = 0;
  }
  else {
    FUN_004282e0(param_1,0);
    FUN_00428400(local_c,local_28);
    uVar2 = FID_conflict_begin(local_14);
    cVar1 = FUN_004221b0(uVar2);
    if (cVar1 == '\0') {
      FUN_004282e0(param_2,0);
      puVar7 = local_34;
      puVar5 = local_8;
      FUN_00421ea0(puVar5,puVar7);
      FUN_00428400(puVar5,puVar7);
      puVar7 = local_18;
      FUN_00421ea0(puVar7);
      uVar2 = FID_conflict_begin(puVar7);
      cVar1 = FUN_004221b0(uVar2);
      if (cVar1 == '\0') {
        iVar3 = FUN_00421ea0();
        uVar2 = *(undefined4 *)(iVar3 + 8);
        iVar3 = FUN_00421ea0(uVar2);
        uVar6 = *(undefined4 *)(iVar3 + 4);
        iVar3 = FUN_00421ea0(uVar6);
        uVar2 = FUN_004324a0(*(undefined4 *)(iVar3 + 0xc),uVar6,uVar2);
        FUN_0042d880(uVar2);
        if (*(char *)(local_10 + 0x1d) != '\0') {
          FUN_00422190();
          while( true ) {
            puVar7 = local_1c;
            FUN_00421ea0(puVar7);
            uVar2 = FID_conflict_begin(puVar7);
            cVar1 = FUN_00420f10(uVar2);
            if (cVar1 == '\0') break;
            puVar4 = (undefined4 *)FUN_00421ea0();
            cVar1 = FUN_004282a0(param_2,*puVar4);
            if (cVar1 != '\0') break;
            iVar3 = FUN_00421ea0();
            uVar2 = *(undefined4 *)(iVar3 + 8);
            iVar3 = FUN_00421ea0(uVar2);
            uVar6 = *(undefined4 *)(iVar3 + 4);
            iVar3 = FUN_00421ea0(uVar6);
            uVar2 = FUN_004324a0(*(undefined4 *)(iVar3 + 0xc),uVar6,uVar2);
            FUN_0042d880(uVar2);
            FUN_00422190();
          }
        }
        uVar2 = 1;
      }
      else {
        uVar2 = 0;
      }
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}


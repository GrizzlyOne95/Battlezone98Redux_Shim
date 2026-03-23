
undefined4 FUN_00612f10(int param_1,int param_2,int param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  byte bVar6;
  
  if (param_1 == 0) {
    uVar4 = 0;
  }
  else if ((param_3 < 0) && (4 < param_3)) {
    uVar4 = 0;
  }
  else {
    iVar2 = FUN_00417ca0();
    if (iVar2 == 0) {
      uVar4 = 0;
    }
    else {
      iVar2 = FUN_00417f40(param_3);
      if (iVar2 == 0) {
        uVar4 = 0;
      }
      else {
        iVar3 = FUN_00417f60(param_3);
        if (iVar3 != 0) {
          FUN_004a77a0(param_3,0);
          FUN_00611590();
        }
        bVar6 = (byte)param_3;
        if (param_2 == 0) {
          uVar5 = FUN_00417fb0();
          FUN_004d9950(~(1 << (bVar6 & 0x1f)) & uVar5);
          uVar5 = FUN_00462510();
          FUN_005c7450(uVar5 & ~(1 << (bVar6 & 0x1f)));
        }
        else {
          uVar4 = (**(code **)(*(int *)(param_1 + 0x18) + 0x30))(iVar2);
          uVar4 = FUN_006121c0(uVar4,iVar2);
          FUN_004a77a0(param_3,uVar4);
          uVar5 = FUN_00417fb0();
          FUN_004d9950(1 << (bVar6 & 0x1f) | uVar5);
          uVar5 = FUN_00462510();
          FUN_005c7450(uVar5 | 1 << (bVar6 & 0x1f));
        }
        FUN_004d9970();
        iVar2 = FUN_0045bdf0();
        if ((iVar2 != 0) && (iVar2 != 1)) {
          cVar1 = FUN_005d7690(&DAT_025f797c);
          if (cVar1 != '\0') {
            FUN_0060b650();
          }
        }
        uVar4 = 1;
      }
    }
  }
  return uVar4;
}


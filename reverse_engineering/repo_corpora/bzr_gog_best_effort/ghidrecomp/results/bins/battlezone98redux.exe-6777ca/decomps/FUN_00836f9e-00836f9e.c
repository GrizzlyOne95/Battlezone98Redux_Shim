
void FUN_00836f9e(int param_1)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  undefined2 *puVar8;
  undefined4 uVar9;
  int local_70;
  undefined1 local_6c [4];
  undefined4 local_68;
  char *local_64;
  char *local_60;
  int local_58;
  undefined4 local_50;
  undefined1 local_48 [64];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  bVar2 = true;
  iVar3 = FUN_008376b6(param_1,&local_70);
  iVar6 = local_70 + 2;
  iVar4 = FUN_0082c9c5(param_1,iVar6);
  if (iVar4 == 0) {
    uVar5 = (uint)(param_1 == iVar3);
  }
  else {
    uVar5 = FUN_0082d338(param_1,iVar6);
    FUN_0082d226(param_1,0xfffffffe);
  }
  iVar4 = FUN_0082c8f6(param_1);
  if (iVar4 == local_70) {
    uVar9 = 0;
    puVar8 = (undefined2 *)&DAT_008a1ad8;
  }
  else {
    iVar4 = FUN_0082c9f5(param_1,local_70 + 1);
    if (iVar4 == 0) goto LAB_00837194;
    uVar9 = 1;
    puVar8 = &DAT_0087a44c;
  }
  FUN_0082cd08(param_1,puVar8,uVar9);
  FUN_0082cd08(param_1,"stack traceback:",0x10);
  iVar4 = FUN_0082e171(iVar3,uVar5,local_6c);
  while (iVar4 != 0) {
    uVar7 = uVar5 + 1;
    if (((int)uVar7 < 0xd) || (!bVar2)) {
      FUN_0082cd08(param_1,&DAT_00883ec4,2);
      FUN_0082e08b(iVar3,&DAT_0086fe80,local_6c);
      FUN_0082cc9e(param_1,&DAT_0086fe84,local_48);
      if (0 < local_58) {
        FUN_0082cc9e(param_1,&DAT_0086fe88,local_58);
      }
      if (*local_64 == '\0') {
        cVar1 = *local_60;
        if (cVar1 == 'm') {
          FUN_0082cc9e(param_1," in main chunk");
        }
        else if ((cVar1 == 'C') || (cVar1 == 't')) {
          FUN_0082cd08(param_1,&DAT_0086feb0,2);
        }
        else {
          FUN_0082cc9e(param_1," in function <%s:%d>",local_48,local_50);
        }
      }
      else {
        FUN_0082cc9e(param_1," in function \'%s\'",local_68);
      }
      iVar4 = FUN_0082c8f6(param_1);
      FUN_0082c61c(param_1,iVar4 - local_70);
    }
    else {
      iVar4 = FUN_0082e171(iVar3,uVar5 + 0xb,local_6c);
      if (iVar4 != 0) {
        FUN_0082cd08(param_1,"\n\t...",5);
        iVar4 = FUN_0082e171(iVar3,uVar5 + 0xb,local_6c);
        uVar5 = uVar7;
        while (iVar4 != 0) {
          iVar4 = FUN_0082e171(iVar3,uVar5 + 0xb,local_6c);
          uVar5 = uVar5 + 1;
        }
      }
      bVar2 = false;
      uVar7 = uVar5;
    }
    iVar4 = FUN_0082e171(iVar3,uVar7,local_6c);
    uVar5 = uVar7;
  }
  iVar3 = FUN_0082c8f6(param_1);
  FUN_0082c61c(param_1,iVar3 - local_70);
LAB_00837194:
  FUN_0083e885();
  return;
}


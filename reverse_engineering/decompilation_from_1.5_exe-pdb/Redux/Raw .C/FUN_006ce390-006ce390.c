
int FUN_006ce390(int param_1,int param_2,uint param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  longlong lVar5;
  longlong lVar6;
  longlong lVar7;
  undefined8 uVar8;
  
  if ((((param_1 < 0) || (param_2 < 0)) || ((int)param_3 < 0)) || ((param_5 < 1 && (param_5 < 0))))
  {
    iVar1 = FUN_006db710(param_1);
    iVar2 = FUN_006db710(param_2);
    iVar3 = FUN_006db710(param_3);
    lVar5 = imaxabs(param_4,param_5);
    lVar6 = __allmul(iVar1,iVar1 >> 0x1f,0xe10,0);
    lVar7 = __allmul(iVar2,iVar2 >> 0x1f,0x3c,0);
    uVar8 = FUN_006d2030();
    lVar6 = __allmul(lVar6 + lVar7 + (longlong)iVar3,uVar8);
    iVar1 = __allmul(lVar5 + lVar6,0xffffffff,0xffffffff);
  }
  else {
    lVar5 = __allmul(param_1,param_1 >> 0x1f,0xe10,0);
    lVar6 = __allmul(param_2,param_2 >> 0x1f,0x3c,0);
    uVar4 = (uint)(lVar5 + lVar6);
    uVar8 = FUN_006d2030();
    iVar1 = __allmul(uVar4 + param_3,
                     (int)((ulonglong)(lVar5 + lVar6) >> 0x20) + ((int)param_3 >> 0x1f) +
                     (uint)CARRY4(uVar4,param_3),uVar8);
    iVar1 = iVar1 + param_4;
  }
  return iVar1;
}


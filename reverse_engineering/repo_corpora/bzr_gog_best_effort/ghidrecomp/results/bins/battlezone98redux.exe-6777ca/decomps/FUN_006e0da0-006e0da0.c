
/* WARNING: Removing unreachable block (ram,0x006e0dbe) */

void FUN_006e0da0(void)

{
  longlong lVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  
  lVar1 = FUN_006ce360();
  if (lVar1 < 1000000) {
    uVar2 = FUN_006ce370();
    uVar3 = FUN_006ce360();
    uVar3 = __alldiv(1000000,0,uVar3);
    __allmul(uVar2,uVar3);
  }
  else {
    uVar2 = FUN_006ce370();
    uVar3 = FUN_006ce360();
    uVar3 = __alldiv(uVar3,1000000,0);
    __alldiv(uVar2,uVar3);
  }
  return;
}


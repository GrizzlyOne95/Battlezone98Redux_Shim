
void FUN_006c9990(void)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar1 = FUN_006ce370();
  uVar2 = FUN_006ce360();
  uVar2 = __allmul(uVar2,0x3c,0);
  uVar1 = __alldiv(uVar1,uVar2);
  __allrem(uVar1,0x3c,0);
  return;
}


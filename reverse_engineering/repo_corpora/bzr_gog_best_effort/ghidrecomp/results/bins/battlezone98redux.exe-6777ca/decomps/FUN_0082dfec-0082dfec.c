
void FUN_0082dfec(int param_1,uint param_2,undefined4 param_3)

{
  uint *puVar1;
  undefined *puVar2;
  uint uVar3;
  int iVar4;
  undefined4 local_8;
  
  local_8 = 0;
  puVar1 = *(uint **)(param_1 + 0x14);
  puVar2 = (&PTR_PTR_0086f0b4)[*(int *)(param_2 + 8)];
  uVar3 = *puVar1;
  do {
    if (puVar1[2] <= uVar3) {
      iVar4 = 0;
LAB_0082e01d:
      if (iVar4 == 0) {
        FUN_0082df5b(param_1,"attempt to %s a %s value",param_3,puVar2);
      }
      else {
        FUN_0082df5b(param_1,"attempt to %s %s \'%s\' (a %s value)",param_3,iVar4,local_8);
      }
      return;
    }
    if (param_2 == uVar3) {
      iVar4 = FUN_0082dc7a(param_1,puVar1,(int)(param_2 - *(int *)(param_1 + 0xc)) >> 4,&local_8);
      goto LAB_0082e01d;
    }
    uVar3 = uVar3 + 0x10;
  } while( true );
}



int FUN_0083018d(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  int local_8;
  
  iVar1 = *(int *)(param_1 + 0x10);
  local_8 = 0;
  iVar3 = 0;
  puVar2 = *(undefined4 **)(iVar1 + 0x70);
  while (puVar4 = puVar2, puVar2 = (undefined4 *)*puVar4, puVar2 != (undefined4 *)0x0) {
    if ((((*(byte *)((int)puVar2 + 5) & 3) != 0) || (param_2 != 0)) &&
       ((*(byte *)((int)puVar2 + 5) & 8) == 0)) {
      iVar3 = puVar2[2];
      if (((iVar3 == 0) || ((*(byte *)(iVar3 + 6) & 4) != 0)) ||
         (iVar3 = FUN_0083347b(iVar3,2,*(undefined4 *)(*(int *)(param_1 + 0x10) + 0xc4)), iVar3 == 0
         )) {
        *(byte *)((int)puVar2 + 5) = *(byte *)((int)puVar2 + 5) | 8;
        iVar3 = local_8;
      }
      else {
        *(byte *)((int)puVar2 + 5) = *(byte *)((int)puVar2 + 5) | 8;
        local_8 = local_8 + 0x18 + puVar2[4];
        *puVar4 = *puVar2;
        if (*(undefined4 **)(iVar1 + 0x30) == (undefined4 *)0x0) {
          *puVar2 = puVar2;
        }
        else {
          *puVar2 = **(undefined4 **)(iVar1 + 0x30);
          **(undefined4 **)(iVar1 + 0x30) = puVar2;
        }
        *(undefined4 **)(iVar1 + 0x30) = puVar2;
        iVar3 = local_8;
        puVar2 = puVar4;
      }
    }
  }
  return iVar3;
}


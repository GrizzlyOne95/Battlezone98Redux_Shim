
char * FUN_0082dc7a(undefined4 param_1,int param_2,uint param_3,int *param_4)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined2 *puVar7;
  undefined8 uVar8;
  
  piVar2 = *(int **)(param_2 + 4);
  if (piVar2[2] == 6) {
    while (*(char *)(*piVar2 + 6) == '\0') {
      iVar1 = *(int *)(*piVar2 + 0x10);
      uVar3 = FUN_0082dad3(param_1,param_2);
      iVar4 = FUN_0082fb1b(iVar1,param_3 + 1,uVar3);
      *param_4 = iVar4;
      if (iVar4 != 0) {
        return "local";
      }
      uVar5 = FUN_0082e24d(iVar1,uVar3,param_3);
      uVar6 = uVar5 & 0x3f;
      if (uVar6 != 0) {
        if (uVar6 == 4) {
          if (*(int *)(iVar1 + 0x1c) == 0) {
            puVar7 = &DAT_0088d940;
          }
          else {
            puVar7 = (undefined2 *)(*(int *)(*(int *)(iVar1 + 0x1c) + (uVar5 >> 0x17) * 4) + 0x10);
          }
          *param_4 = (int)puVar7;
          return "upvalue";
        }
        if (uVar6 != 5) {
          if ((uVar6 != 6) && (uVar6 != 0xb)) {
            return (char *)0x0;
          }
          uVar8 = FUN_0082ddb5(iVar1,uVar5 >> 0xe & 0x1ff);
          *param_4 = (int)uVar8;
          return (char *)((ulonglong)uVar8 >> 0x20);
        }
        *param_4 = *(int *)(*(int *)(iVar1 + 8) + (uVar5 >> 0xe) * 0x10) + 0x10;
        return "global";
      }
      param_3 = uVar5 >> 0x17;
      if ((uVar5 >> 6 & 0xff) <= param_3) {
        return (char *)0x0;
      }
      piVar2 = *(int **)(param_2 + 4);
      if (piVar2[2] != 6) {
        return (char *)0x0;
      }
    }
  }
  return (char *)0x0;
}


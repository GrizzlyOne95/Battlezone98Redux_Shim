
void __fastcall FUN_005f7cf0(int param_1)

{
  char cVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_5;
  
  if (*(int *)(param_1 + 8) != 0xd) {
    uVar3 = FUN_00462630(*(undefined4 *)(param_1 + 0x14));
    *(undefined4 *)(param_1 + 0x18) = uVar3;
    if (((*(int *)(param_1 + 0x18) == 0) ||
        (cVar1 = FUN_004db510(*(undefined4 *)(param_1 + 0x18)), cVar1 != '\0')) ||
       (iVar4 = FUN_00417ca0(), iVar4 == 0)) {
      *(undefined4 *)(param_1 + 0xc) = 0xd;
    }
    else {
      cVar1 = FUN_00603ad0();
      if (*(int *)(param_1 + 8) == 5) {
        FUN_006057e0();
      }
      cVar2 = FUN_00608460();
      if (cVar2 == '\0') {
        if ((cVar1 == '\0') ||
           (cVar1 = FUN_00462b60(*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0xd4),
                                 *(undefined4 *)(param_1 + 0xf4),0x3f800000), cVar1 != '\0')) {
          local_5 = 0;
        }
        else {
          local_5 = 1;
        }
        FUN_00604130(local_5);
      }
      else {
        cVar1 = FUN_00608490();
        if (cVar1 != '\0') {
          FUN_006084c0();
        }
      }
      FUN_00605560();
    }
  }
  return;
}


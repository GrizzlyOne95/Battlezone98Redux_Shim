
undefined4 __thiscall FUN_004ae110(int param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  if (param_2 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = (**(code **)(*(int *)(param_2 + 0x18) + 0x30))();
    iVar3 = FUN_0046fc10(uVar2);
    if (iVar3 == 1) {
      if (param_2 == param_1) {
        uVar2 = 0;
      }
      else {
        iVar3 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
        if (*(int *)(iVar3 + 0x14) == 0x53435250) {
          uVar2 = 0;
        }
        else {
          iVar3 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
          if (*(int *)(iVar3 + 0x14) == 0x4745495a) {
            uVar2 = 0;
          }
          else {
            iVar3 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
            if (*(int *)(iVar3 + 0x1c) == 3) {
              uVar2 = 3;
            }
            else {
              cVar1 = FUN_004db5b0(param_2);
              if (cVar1 == '\0') {
                iVar3 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
                if ((*(int *)(iVar3 + 0x1c) != 1) &&
                   (iVar3 = (*(code *)**(undefined4 **)(param_2 + 0x18))(),
                   *(int *)(iVar3 + 0x1c) != 6)) {
                  iVar3 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
                  if ((*(int *)(iVar3 + 0x1c) == 5) && (cVar1 = FUN_0046fbf0(), cVar1 == '\0')) {
                    return 0;
                  }
                  return 0xf;
                }
                uVar2 = 5;
              }
              else if (*(int *)(param_1 + 0x1a0) == 0) {
                uVar2 = 0;
              }
              else {
                uVar2 = 4;
              }
            }
          }
        }
      }
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}



undefined4 __thiscall FUN_005f5d10(int param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  if (param_2 == 0) {
    uVar2 = 0;
  }
  else {
    iVar3 = FUN_0046fc10();
    if (iVar3 == 0) {
      uVar2 = 0;
    }
    else if (iVar3 == 1) {
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
              iVar3 = (**(code **)(*(int *)(param_2 + 0x18) + 4))();
              if ((iVar3 == 0) && (cVar1 = FUN_0046fbf0(), cVar1 == '\0')) {
                return 0;
              }
              cVar1 = FUN_004db5b0(param_2);
              if (cVar1 == '\0') {
                iVar3 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
                if ((*(int *)(iVar3 + 0x1c) != 1) &&
                   (iVar3 = (*(code *)**(undefined4 **)(param_2 + 0x18))(),
                   *(int *)(iVar3 + 0x1c) != 6)) {
                  iVar3 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
                  if (*(int *)(iVar3 + 0x1c) == 5) {
                    return 0;
                  }
                  return 0xf;
                }
                uVar2 = 5;
              }
              else {
                uVar2 = 0;
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


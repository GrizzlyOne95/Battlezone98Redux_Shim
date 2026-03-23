
void FUN_00831f3a(int param_1,int param_2,int param_3)

{
  uint uVar1;
  size_t _Size;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  int local_14;
  int local_c;
  int local_8;
  
  do {
    iVar7 = (param_3 + 1) * 0x10 + *(int *)(param_1 + 0xc);
    local_14 = 2;
    if (((*(int *)(iVar7 + -0x18) == 4) || (*(int *)(iVar7 + -0x18) == 3)) &&
       ((*(int *)(iVar7 + -8) == 4 || (iVar2 = FUN_00833372(param_1,iVar7 + -0x10), iVar2 != 0)))) {
      iVar2 = *(int *)(*(int *)(iVar7 + -0x10) + 0xc);
      if (iVar2 == 0) {
        if (*(int *)(iVar7 + -0x18) != 4) {
          FUN_00833372(param_1,iVar7 + -0x20);
        }
      }
      else {
        iVar6 = 1;
        local_14 = 1;
        if (1 < param_2) {
          piVar5 = (int *)(iVar7 + -0x20);
          do {
            if ((piVar5[2] != 4) &&
               (iVar3 = FUN_00833372(param_1,piVar5), local_14 = iVar6, iVar3 == 0)) break;
            uVar1 = *(uint *)(*piVar5 + 0xc);
            if (-iVar2 - 3U <= uVar1) {
              FUN_0082df5b(param_1,"string length overflow");
            }
            iVar2 = iVar2 + uVar1;
            piVar5 = piVar5 + -4;
            iVar6 = iVar6 + 1;
            local_14 = iVar6;
          } while (iVar6 < param_2);
        }
        iVar2 = FUN_0082ecad(param_1,*(int *)(param_1 + 0x10) + 0x34,iVar2);
        local_8 = 0;
        if (0 < local_14) {
          local_8 = 0;
          piVar5 = (int *)(iVar7 + local_14 * -0x10);
          local_c = local_14;
          do {
            _Size = *(size_t *)(*piVar5 + 0xc);
            memcpy((void *)(iVar2 + local_8),(void *)(*piVar5 + 0x10),_Size);
            piVar5 = piVar5 + 4;
            local_8 = local_8 + _Size;
            local_c = local_c + -1;
          } while (0 < local_c);
        }
        puVar8 = (undefined4 *)(iVar7 + local_14 * -0x10);
        uVar4 = FUN_008309f4(param_1,iVar2,local_8);
        *puVar8 = uVar4;
        puVar8[2] = 4;
      }
    }
    else {
      iVar2 = FUN_00831d18(param_1,iVar7 + -0x20,iVar7 + -0x10,iVar7 + -0x20,0xf);
      if (iVar2 == 0) {
        FUN_0082de60(param_1,iVar7 + -0x20,iVar7 + -0x10);
      }
    }
    param_2 = param_2 + (1 - local_14);
    param_3 = param_3 + (1 - local_14);
    if (param_2 < 2) {
      return;
    }
  } while( true );
}


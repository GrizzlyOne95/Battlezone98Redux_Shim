
undefined4 FUN_00823700(int param_1,int param_2,uint param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *(int *)(param_1 + 8);
  if ((*(uint *)(iVar1 + 0x120) & 0x100) == 0) {
    return 0;
  }
  if (param_2 == 0x100) {
    switch(param_3) {
    case 8:
      if (*(uint *)(iVar1 + 0x108) < *(uint *)(iVar1 + 0x110)) {
        memmove((void *)(iVar1 + 0xf + *(int *)(iVar1 + 0x110)),
                (void *)(iVar1 + 0x10 + *(int *)(iVar1 + 0x110)),
                (*(int *)(iVar1 + 0x104) + 2) - *(int *)(iVar1 + 0x110));
        *(int *)(iVar1 + 0x110) = *(int *)(iVar1 + 0x110) + -1;
        *(int *)(iVar1 + 0x10c) = *(int *)(iVar1 + 0x10c) + -1;
        FUN_00822f10(iVar1,*(undefined4 *)(iVar1 + 0x110));
        FUN_00823090(iVar1,*(undefined4 *)(iVar1 + 0x10c));
      }
      *(uint *)(iVar1 + 0x120) = *(uint *)(iVar1 + 0x120) | 0x200;
      uVar2 = 1;
      break;
    default:
      goto LAB_00823c7f;
    case 0xd:
      if (*(int *)(iVar1 + 0x124) != 0) {
        (**(code **)(iVar1 + 0x124))(param_1,iVar1 + 0x10 + *(int *)(iVar1 + 0x108));
      }
      *(uint *)(iVar1 + 0x120) = *(uint *)(iVar1 + 0x120) | 0x200;
      uVar2 = 2;
      break;
    case 0x1b:
      memset((void *)(iVar1 + 0x10),0,0xf0);
      *(undefined4 *)(iVar1 + 0x10c) = 0;
      *(undefined4 *)(iVar1 + 0x110) = 0;
      if (*(int *)(iVar1 + 0x124) != 0) {
        (**(code **)(iVar1 + 0x124))(param_1,0);
      }
      *(uint *)(iVar1 + 0x120) = *(uint *)(iVar1 + 0x120) | 0x200;
      uVar2 = 2;
      break;
    case 0x23:
      if (*(int *)(iVar1 + 0x10c) + 1U < *(uint *)(iVar1 + 0x104)) {
        *(int *)(iVar1 + 0x110) = *(int *)(iVar1 + 0x10c) + 1;
        FUN_00822f40(iVar1,*(undefined4 *)(iVar1 + 0x110));
      }
      else {
        *(undefined4 *)(iVar1 + 0x110) = *(undefined4 *)(iVar1 + 0x10c);
        FUN_00822f40(iVar1,*(undefined4 *)(iVar1 + 0x10c));
      }
      *(uint *)(iVar1 + 0x120) = *(uint *)(iVar1 + 0x120) | 0x200;
      uVar2 = 1;
      break;
    case 0x24:
      *(undefined4 *)(iVar1 + 0x110) = *(undefined4 *)(iVar1 + 0x108);
      FUN_00822f10(iVar1,0);
      *(uint *)(iVar1 + 0x120) = *(uint *)(iVar1 + 0x120) | 0x200;
      uVar2 = 1;
      break;
    case 0x25:
      if (*(uint *)(iVar1 + 0x108) < *(uint *)(iVar1 + 0x110)) {
        *(int *)(iVar1 + 0x110) = *(int *)(iVar1 + 0x110) + -1;
        FUN_00822f10(iVar1,*(undefined4 *)(iVar1 + 0x110));
      }
      *(uint *)(iVar1 + 0x120) = *(uint *)(iVar1 + 0x120) | 0x200;
      uVar2 = 1;
      break;
    case 0x26:
      if (*(int *)(iVar1 + 0x128) != 0) {
        (**(code **)(iVar1 + 0x128))(param_1,1);
      }
      uVar2 = 1;
      break;
    case 0x27:
      if (*(uint *)(iVar1 + 0x110) <= *(uint *)(iVar1 + 0x10c)) {
        *(int *)(iVar1 + 0x110) = *(int *)(iVar1 + 0x110) + 1;
        FUN_00822f40(iVar1,*(undefined4 *)(iVar1 + 0x110));
      }
      *(uint *)(iVar1 + 0x120) = *(uint *)(iVar1 + 0x120) | 0x200;
      uVar2 = 1;
      break;
    case 0x28:
      if (*(int *)(iVar1 + 0x128) != 0) {
        (**(code **)(iVar1 + 0x128))(param_1,0);
      }
      uVar2 = 1;
      break;
    case 0x2e:
      if (*(uint *)(iVar1 + 0x110) < *(int *)(iVar1 + 0x10c) + 1U) {
        memmove((void *)(iVar1 + 0x10 + *(int *)(iVar1 + 0x110)),
                (void *)(iVar1 + 0x11 + *(int *)(iVar1 + 0x110)),0xef - *(int *)(iVar1 + 0x110));
        *(undefined1 *)(iVar1 + 0xff) = 0;
        *(int *)(iVar1 + 0x10c) = *(int *)(iVar1 + 0x10c) + -1;
        FUN_00823090(iVar1,*(undefined4 *)(iVar1 + 0x10c));
      }
      *(uint *)(iVar1 + 0x120) = *(uint *)(iVar1 + 0x120) | 0x200;
      uVar2 = 1;
    }
  }
  else {
    if (param_2 == 0x102) {
      if ((0x1f < param_3) && (param_3 < 0x100)) {
        if (*(int *)(iVar1 + 0x10c) == *(int *)(iVar1 + 0x104)) {
          return 1;
        }
        memmove((void *)(iVar1 + 0x11 + *(int *)(iVar1 + 0x110)),
                (void *)(iVar1 + 0x10 + *(int *)(iVar1 + 0x110)),
                (*(int *)(iVar1 + 0x104) + 2) - *(int *)(iVar1 + 0x110));
        *(undefined1 *)(iVar1 + 0x10 + *(int *)(iVar1 + 0x110)) = (undefined1)param_3;
        *(int *)(iVar1 + 0x110) = *(int *)(iVar1 + 0x110) + 1;
        *(int *)(iVar1 + 0x10c) = *(int *)(iVar1 + 0x10c) + 1;
        *(uint *)(iVar1 + 0x120) = *(uint *)(iVar1 + 0x120) | 0x200;
        FUN_00822f40(iVar1,*(undefined4 *)(iVar1 + 0x110));
        return 1;
      }
      return 0;
    }
LAB_00823c7f:
    uVar2 = 0;
  }
  return uVar2;
}


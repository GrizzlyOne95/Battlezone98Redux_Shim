
undefined4
FUN_00589920(undefined4 param_1,undefined4 param_2,undefined1 *param_3,undefined1 param_4)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  
  puVar1 = (undefined1 *)FUN_00589620(param_1,param_2);
  if (puVar1 == (undefined1 *)0x0) {
    if (param_3 != (undefined1 *)0x0) {
      *param_3 = param_4;
    }
    uVar2 = 0;
  }
  else {
    if (param_3 != (undefined1 *)0x0) {
      switch(*puVar1) {
      case 0x30:
      case 0x46:
      case 0x4e:
      case 0x66:
      case 0x6e:
        *param_3 = 0;
        break;
      case 0x31:
      case 0x54:
      case 0x59:
      case 0x74:
      case 0x79:
        *param_3 = 1;
        break;
      default:
        *param_3 = param_4;
      }
    }
    uVar2 = 1;
  }
  return uVar2;
}


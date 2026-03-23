
void FUN_0083cafa(int *param_1,undefined4 param_2,int *param_3,int *param_4)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  switch(param_2) {
  case 0:
    uVar4 = 0xc;
    break;
  case 1:
    uVar4 = 0xd;
    break;
  case 2:
    uVar4 = 0xe;
    break;
  case 3:
    uVar4 = 0xf;
    break;
  case 4:
    uVar4 = 0x10;
    break;
  case 5:
    uVar4 = 0x11;
    break;
  case 6:
    FUN_0083c835(param_1,param_4);
    if ((*param_4 == 0xb) &&
       (((byte)*(undefined4 *)(*(int *)(*param_1 + 0xc) + param_4[2] * 4) & 0x3f) == 0x15)) {
      FUN_0083c3b1(param_1,param_3);
      *(uint *)(*(int *)(*param_1 + 0xc) + param_4[2] * 4) =
           *(uint *)(*(int *)(*param_1 + 0xc) + param_4[2] * 4) & 0x7fffff | param_3[2] << 0x17;
      *param_3 = 0xb;
      param_3[2] = param_4[2];
      return;
    }
    FUN_0083c800(param_1,param_4);
    FUN_0083be46(param_1,0x15,param_3,param_4);
    return;
  case 7:
    uVar4 = 0;
    goto LAB_0083cc1e;
  case 8:
    uVar4 = 1;
LAB_0083cc1e:
    uVar3 = 0x17;
LAB_0083cc56:
    FUN_0083bed9(param_1,uVar3,uVar4,param_3,param_4);
    return;
  case 9:
    uVar4 = 1;
    goto LAB_0083cc34;
  case 10:
    uVar4 = 1;
    goto LAB_0083cc54;
  case 0xb:
    uVar4 = 0;
LAB_0083cc34:
    uVar3 = 0x18;
    goto LAB_0083cc56;
  case 0xc:
    uVar4 = 0;
LAB_0083cc54:
    uVar3 = 0x19;
    goto LAB_0083cc56;
  case 0xd:
    FUN_0083c667(param_1,param_4);
    piVar1 = param_4 + 5;
    iVar2 = param_3[5];
    goto LAB_0083cb28;
  case 0xe:
    FUN_0083c667(param_1,param_4);
    piVar1 = param_4 + 4;
    iVar2 = param_3[4];
LAB_0083cb28:
    FUN_0083c626(param_1,piVar1,iVar2);
    for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
      *param_3 = *param_4;
      param_4 = param_4 + 1;
      param_3 = param_3 + 1;
    }
  default:
    goto switchD_0083cb0c_default;
  }
  FUN_0083be46(param_1,uVar4,param_3,param_4);
switchD_0083cb0c_default:
  return;
}


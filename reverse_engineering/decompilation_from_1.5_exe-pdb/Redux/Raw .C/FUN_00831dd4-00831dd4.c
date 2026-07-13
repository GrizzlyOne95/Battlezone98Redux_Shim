
uint FUN_00831dd4(int param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  byte bVar3;
  
  if (((param_2 != 0) &&
      (bVar3 = (byte)(1 << ((byte)param_4 & 0x1f)), (*(byte *)(param_2 + 6) & bVar3) == 0)) &&
     (uVar1 = FUN_0083347b(param_2,param_4,
                           *(undefined4 *)(*(int *)(param_1 + 0x10) + 0xbc + param_4 * 4)),
     uVar1 != 0)) {
    if (param_2 == param_3) {
      return uVar1;
    }
    if (((param_3 != 0) && ((*(byte *)(param_3 + 6) & bVar3) == 0)) &&
       (iVar2 = FUN_0083347b(param_3,param_4,
                             *(undefined4 *)(*(int *)(param_1 + 0x10) + 0xbc + param_4 * 4)),
       iVar2 != 0)) {
      iVar2 = FUN_0082eafa(uVar1,iVar2);
      return -(uint)(iVar2 != 0) & uVar1;
    }
  }
  return 0;
}


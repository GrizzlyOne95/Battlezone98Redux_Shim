
undefined1 FUN_00780dc0(undefined4 param_1,undefined4 param_2)

{
  ushort uVar1;
  ushort *puVar2;
  
  puVar2 = (ushort *)FUN_004c0fe0(param_1,param_2);
  uVar1 = *puVar2;
  return (&DAT_02c06778)
         [((int)(uVar1 & 0x80) >> 7) +
          (uVar1 & 3) * 2 + ((int)(uVar1 & 0xf00) >> 8) * 8 + ((int)(uVar1 & 0xf000) >> 0xc) * 0x40]
  ;
}


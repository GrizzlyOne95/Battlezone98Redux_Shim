
void * FUN_0062f430(void)

{
  undefined4 *puVar1;
  undefined1 local_14 [12];
  void *local_8;
  
  local_8 = malloc(0x124);
  memset(local_8,0,0x124);
  FUN_00442900((int)local_8 + 0x4c);
  FUN_00444970((int)local_8 + 4);
  FUN_00444a80((int)local_8 + 4,0x44bb8000,0x44bb8000);
  *(undefined4 *)((int)local_8 + 0xc4) = 0;
  *(undefined4 *)((int)local_8 + 0xd0) = 0;
  *(undefined4 *)((int)local_8 + 0xd4) = 0;
  *(undefined4 *)((int)local_8 + 0xd8) = 0;
  *(undefined4 *)((int)local_8 + 0xdc) = 0;
  *(undefined4 *)((int)local_8 + 0xe0) = 0;
  *(undefined4 *)((int)local_8 + 0xe4) = 0;
  puVar1 = (undefined4 *)FUN_00440000(local_14,0,0,0);
  *(undefined4 *)((int)local_8 + 0xf0) = *puVar1;
  *(undefined4 *)((int)local_8 + 0xf4) = puVar1[1];
  *(undefined4 *)((int)local_8 + 0xf8) = puVar1[2];
  *(undefined4 *)((int)local_8 + 0xfc) = 0;
  *(undefined4 *)((int)local_8 + 0x100) = 0;
  *(undefined4 *)((int)local_8 + 0x110) = 0;
  *(undefined4 *)((int)local_8 + 0x114) = 0;
  *(undefined2 *)((int)local_8 + 0x11c) = 0;
  *(undefined2 *)((int)local_8 + 0x11e) = 0;
  *(undefined4 *)((int)local_8 + 0x120) = 0;
  return local_8;
}


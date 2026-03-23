
void FUN_00679570(RenderQueue *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined1 local_18 [4];
  Renderable *local_14;
  int local_10;
  undefined1 local_c [4];
  int local_8;
  
  cVar1 = FUN_006796b0();
  if ((cVar1 != '\0') && (*(char *)(local_8 + 0xd8) != '\0')) {
    local_10 = local_8 + 0x1a4;
    FID_conflict_begin(local_c);
    FID_conflict_end(local_18);
    while( true ) {
      cVar1 = FID_conflict_operator__(local_18);
      if (cVar1 == '\0') break;
      puVar2 = (undefined4 *)FUN_00421ec0();
      local_14 = (Renderable *)*puVar2;
      Ogre::RenderQueue::addRenderable(param_1,local_14,(uchar)local_14[0xac]);
      FUN_00421ee0();
    }
  }
  return;
}


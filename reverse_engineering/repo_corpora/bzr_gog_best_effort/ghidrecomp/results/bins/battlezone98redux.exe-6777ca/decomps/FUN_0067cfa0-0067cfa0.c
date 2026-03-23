
void FUN_0067cfa0(SceneNode *param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_24 [12];
  undefined1 local_18 [12];
  undefined4 local_c;
  SceneManager *local_8;
  
  if (param_1 != (SceneNode *)0x0) {
    (**(code **)(*(int *)param_1 + 0x15c))(local_18);
    while (cVar1 = FUN_00666820(), cVar1 != '\0') {
      local_8 = Ogre::SceneNode::getCreator(param_1);
      uVar2 = FUN_00683af0();
      (**(code **)(*(int *)local_8 + 0x48c))(uVar2);
    }
    (**(code **)(*(int *)param_1 + 0xa0))(local_24);
    while (cVar1 = FUN_00666820(), cVar1 != '\0') {
      local_c = FUN_00683af0();
      FUN_0067cfa0(local_c);
    }
  }
  return;
}


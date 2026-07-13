/*
 * Entry: 004cedce
 * Name: HoverInterface::Render
 * Namespace: HoverInterface
 * Signature: void Render(HoverInterface * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall HoverInterface::Render(HoverInterface *this)

{
  float fVar1;
  
  DisplayInterface::PrintClear((DisplayInterface *)this);
  DisplayInterface::PrintValue((DisplayInterface *)this,"throt",this->throt);
  DisplayInterface::PrintValue((DisplayInterface *)this,"steer",this->steer);
  DisplayInterface::PrintValue((DisplayInterface *)this,"straf",this->straf);
  DisplayInterface::PrintValue((DisplayInterface *)this,"brake",this->brake);
  DisplayInterface::PrintValue((DisplayInterface *)this,"posit",this->pos);
  DisplayInterface::PrintValue((DisplayInterface *)this,"veloc",this->vel);
  fVar1 = VecLen(this->vel);
  DisplayInterface::PrintValue((DisplayInterface *)this,"veloc",fVar1);
  DisplayInterface::PrintValue((DisplayInterface *)this,"accel",this->accel);
  fVar1 = VecLen(this->accel);
  DisplayInterface::PrintValue((DisplayInterface *)this,"accel",fVar1);
  DisplayInterface::PrintValue((DisplayInterface *)this,"heightRatio",this->heightRatio);
  DisplayInterface::PrintValue((DisplayInterface *)this,"thrustRatio",this->thrustRatio);
  DisplayInterface::PrintValue((DisplayInterface *)this,"trackRatio",this->trackRatio);
  return;
}

#include "../headers/Core.hpp"

clsTransform::clsTransform() {}

clsTransform::clsTransform(float PosX, float PosY, float Width, float Height, float Gravity, float RotCW, float RotCCW)
  : m_PosX(PosX), m_PosY(PosY), m_Gravity(Gravity), m_Width(Width),
    m_Height(Height), m_RotCW(RotCW), m_RotCCW(RotCCW)
{
}

void clsTransform::SetWidth(const float &Width)
{
  this->m_Width = Width;
}

float clsTransform::GetWidth() const
{
  return (this->m_Width);
}
  
void clsTransform::SetHeight(const float &Height)
{
  this->m_Height = Height;
}

float clsTransform::GetHeight() const
{
  return (this->m_Height);
}

void clsTransform::SetGravity(const float &Gravity)
{
  m_Gravity = Gravity;
}

float clsTransform::GetGravity() const
{
  return (m_Gravity);
}

void clsTransform::SetPosX(const float &PosX)
{
  this->m_PosX += PosX;
}

void clsTransform::SetPosY(const float &PosY)
{
  this->m_PosY += PosY;
}

void clsTransform::SetPosXY(const float &PosX, const float &PosY)
{
  this->m_PosX += PosX;
  this->m_PosY += PosY;
}

void clsTransform::SetDefaultPos(const float &PosX, const float &PosY)
{
  this->m_PosX = PosX;
  this->m_PosY = PosY;
}

float clsTransform::GetPosX() const
{
  return (m_PosX);
}

float clsTransform::GetPosY() const
{
  return (m_PosY);
}

void clsTransform::SetRot(const float &RotCW)
{
  this->m_RotCW = RotCW;
}

void clsTransform::SetRotCW(const float &RotCW)
{
  this->m_RotCW = RotCW;
}

void clsTransform::SetRotCCW(const float &RotCCW)
{
  this->m_RotCCW = RotCCW;
}

float clsTransform::GetRot() const
{
  return (m_RotCW);
}

float clsTransform::GetRotCW() const
{
  return (m_RotCW);
}

float clsTransform::GetRotCCW() const
{
  return (m_RotCCW);
}


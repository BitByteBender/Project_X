#include "../headers/Core.hpp"

clsCShape::clsCShape()
{
}

clsCShape::clsCShape(char ShapeType, uint16_t Clr[5], float PosX, float PosY, float Width, float Height, float Gravity, float RotCW, float RotCCW)
  : clsTransform(PosX, PosY, Width, Height, Gravity, RotCW, RotCCW), m_Shape(nullptr), m_Color(nullptr), m_CTransform(nullptr)
{
  m_CTransform = new clsTransform(PosX, PosY, Width, Height, Gravity, RotCW, RotCCW);
  SetShape(ShapeType);
  *m_Shape = GetShape();
  Clr[4] == 0 ? SetColor() : SetColor(Clr);
  *m_Color = GetColor();
  //m_Shape->setFillColor(*m_Color);
  SetShapeColor(*m_Color);
  SetInitPos(m_CTransform->GetPosX(), m_CTransform->GetPosY());
}

void clsCShape::SetShape(char ShapeType)
{
  switch (ShapeType) {
  case (enShapeTypes::Rectangle):
    m_Shape = new sf::RectangleShape({clsTransform::GetWidth(), clsTransform::GetHeight()});
    break;
  case (enShapeTypes::Circle):
    m_Shape = new sf::CircleShape(clsTransform::GetWidth());
    break;
  case (enShapeTypes::Triangle):
    m_Shape = new sf::CircleShape(clsTransform::GetWidth(), 3);
    break;
  case (enShapeTypes::Octagon):
    m_Shape = new sf::CircleShape(clsTransform::GetWidth(), 8);
    break;
  case (enShapeTypes::Hexagon):
    m_Shape = new sf::CircleShape(clsTransform::GetWidth(), 6);
    break;
  case (enShapeTypes::Square):
    m_Shape = new sf::RectangleShape({clsTransform::GetWidth(), clsTransform::GetHeight()});
    break;
  default:
    break;
  }
}
  
void clsCShape::SetColor(const uint16_t Clr[5])
{
  m_Color = new sf::Color(Clr[0], Clr[1], Clr[2], Clr[3]);
}

void clsCShape::SetColor()
{
  m_Color = new sf::Color(sf::Color::Red);
}

void clsCShape::SetColor(const sf::Color &Color)
{
  m_Color = new sf::Color(Color);
}

void clsCShape::SetShapeColor(const sf::Color &Color)
{
  m_Shape->setFillColor(Color);
}

sf::Shape &clsCShape::GetShape() const
{
  return (*m_Shape);
}

sf::Color &clsCShape::GetColor() const
{
  return (*m_Color);
}

sf::Color &clsCShape::GetShapeColor() const
{
  return (*m_Color);
}

void clsCShape::SetInitPos(const float &PosX, const float &PosY)
{
  m_CTransform->SetDefaultPos(PosX, PosY);
  GetShape().setPosition({m_CTransform->GetPosX(), m_CTransform->GetPosY()});
}

void clsCShape::SetTransformX(const float &PosX)
{
  m_CTransform->SetPosX(PosX);
  GetShape().setPosition({m_CTransform->GetPosX(),  m_CTransform->GetPosY()});
}

void clsCShape::SetTransformY(const float &PosY)
{
  m_CTransform->SetPosY(PosY);
  GetShape().setPosition({m_CTransform->GetPosX(),  m_CTransform->GetPosY()});
}

void clsCShape::SetTransformXY(const float &PosX, const float &PosY)
{
  m_CTransform->SetPosX(PosX);
  m_CTransform->SetPosY(PosY);
  GetShape().setPosition({m_CTransform->GetPosX(),  m_CTransform->GetPosY()});
}

//void clsCShape::SetDfltPos(const float &PosX, const float &PosY)
void clsCShape::SetDfltPos(void)
{
  //m_CTransform->SetDefaultPos(PosX, PosY);
  SetInitPos(m_CTransform->GetPosX(), m_CTransform->GetPosY());
}

void clsCShape::SetRotationCW(const float &Rot)
{
  m_CTransform->SetRotationCW(Rot);
  GetShape().rotate(sf::degrees(m_CTransform->GetRotationCW()));
}


void clsCShape::SetRotationCCW(const float &Rot)
{
  clsCShape::SetRotationCW(Rot * (-1));
}

clsCShape::~clsCShape()
{
  if (m_Shape != nullptr)
    delete m_Shape;
  
  if (m_Color != nullptr)
    delete m_Color;
  
  if (m_CTransform != nullptr)
    delete [] m_CTransform;
}

#ifndef Core_H
#define Core_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <cstdint>
#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

class clsTransform
{
private:
  float m_PosX = 0.f, m_PosY = 0.f, m_Gravity = 0.f;
  float m_Width = 0.f, m_Height = 0.f;
  float m_RotCW = 0.f, m_RotCCW = 0.f;
  
public:
  clsTransform();
  clsTransform(float PosX, float PosY, float Width, float Height, float Gravity, float m_RotCW, float m_RotCCW);

  void SetWidth(const float &Width);
  float GetWidth() const;
  void SetHeight(const float &Height);
  float GetHeight() const;
  void SetGravity(const float &Gravity);
  float GetGravity() const;
  void SetPosX(const float &PosX);
  void SetPosY(const float &PosY);
  void SetPosXY(const float &PosX, const float &PosY);  
  float GetPosX() const;
  float GetPosY() const;
  void SetDefaultPos(const float &PosX, const float &PosY);
  void SetRotationCW(const float &RotCW);
  void SetRotationCCW(const float &RotCCW);
  float GetRotationCW() const;
  float GetRotationCCW() const;
};

class clsCShape : public clsTransform
{
private:
  enum enShapeTypes {
    Rectangle = 'r',
    Circle = 'c',
    Triangle = 't',
    Octagon = 'o',
    Hexagon = 'h',
    Square = 's',
  };
  
  sf::Shape *m_Shape = nullptr;
  sf::Color *m_Color = nullptr;
  clsTransform *m_CTransform = nullptr;
  
public:
  clsCShape();
  clsCShape(char ShapeType, uint16_t Clr[5], float PosX, float PosY, float Width, float Height, float Gravity, float RotCW, float RotCCW);

  void SetShape(char ShapeType); 
  void SetColor(const uint16_t Clr[5]);
  void SetColor();
  void SetColor(const sf::Color &Color);
  void SetShapeColor(const sf::Color &Color);
  sf::Shape &GetShape() const;
  sf::Color &GetColor() const;
  sf::Color &GetShapeColor() const;
  void SetInitPos(const float &PosX, const float &PosY);
  void SetTransformX(const float &PosX);
  void SetTransformY(const float &PosY);
  void SetTransformXY(const float &PosX, const float &PosY);
  void SetDfltPos(const float &PosX, const float &PosY);
  void SetDfltPos(void);
  void SetRotationCW(const float &Rot);
  void SetRotationCCW(const float &Rot);
  ~clsCShape();
};
#endif /* Core */

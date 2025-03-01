#include "imgui.h"
#include "imgui-SFML.h"
#include "headers/Core.hpp"

bool opened = true;

using std::vector;

int main() {
    sf::RenderWindow window(sf::VideoMode({1200, 600}), "Project X - 2D Engine");
    window.setFramerateLimit(60);
    (void) ImGui::SFML::Init(window);
    ImGui::LoadIniSettingsFromDisk("imgui.ini");
    ImGui::SetNextWindowPos(ImVec2(850, 0));

    uint16_t ColorArr[5] = {75, 52, 93, 255, 0};
    clsCShape shape('r', ColorArr, 50.f, 50.f, 350.f, 100.f, 0);
    
    sf::Clock deltaClock;

    float i = 0.f, j = 0.f, CurrentPosX = 2.f, CurrentPosY = 2.f;
    bool Trigger = false, is_Active = false;
    std::string Shapes = "stohcr";
    uint16_t s = 0;
    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());
	ImGui::SetNextWindowSize(ImVec2(350, 600));
	ImGui::Begin("##CustomWindow", &opened, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse);

	// Calculate centered position for the title text
	float windowWidth = ImGui::GetWindowWidth();
	float textWidth   = ImGui::CalcTextSize("World Editor").x;
	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);

	//ImGui::PushFont(LargeFont);
	// Render the title text
	ImGui::Text("World Editor");
	//ImGui::PopFont();
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
	if (ImGui::TreeNode("Animation Tab")) {
	  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(5.0f, 0.0f, 4.0f, 1.0f));
	  

	  if (ImGui::Button("Animate X-Axis")) {
	    is_Active = true;
	  }
	  ImGui::SameLine();
	  if (is_Active == true) {
	    if (ImGui::Button("Stop Animation")) {
	      shape.SetTransformX(CurrentPosX - 2.0f);
	      i = 0;
	      is_Active = false;
	    }
	  }
	  ImGui::SameLine();
	  if (ImGui::Button("Reset")) {
	    CurrentPosX = 2.0f, CurrentPosY = 2.0f;
	    shape.SetInitPos(CurrentPosX, CurrentPosY);
	    is_Active = false;
	    i = 0;
	  }
	  ImGui::TreePop();
	  ImGui::PopStyleColor();
	}

	if (ImGui::TreeNode("Transform Tools")) {
	  if (ImGui::Button("Transform X")) shape.SetTransformX(CurrentPosX + 5.0f);
	  ImGui::SameLine();
	  if (ImGui::Button("Transform Y")) shape.SetTransformY(CurrentPosY + 5.0f);
	  ImGui::SameLine();
	  if (ImGui::Button("Transform XY")) shape.SetTransformXY(CurrentPosX + 5.0f, CurrentPosY + 5.0f);
	  ImGui::TreePop();
	}

	if (ImGui::TreeNode("Shape Tool")) {
	  float Width = 50.f;
	  if (ImGui::Button("Random Shape")) {
	    shape.SetWidth(Width);
	    s == 0 ? shape.SetHeight(Width) : shape.SetHeight(Width * 2);
	    shape.SetShape(Shapes[s]);
	    s++;
	    if (s > 5) s = 0;
	  }
	  ImGui::SameLine();
	  if (ImGui::Button("Random Color")) shape.SetShapeColor(sf::Color(75 + j, j + 45, j * 5));
	  j++;
	  ImGui::TreePop();
	}

	ImGui::PopStyleColor();
	ImGui::End();
	
	if (is_Active == true) {
	    if (i == 0) Trigger = true;
	    if (Trigger == false) {
	      shape.SetTransformX(CurrentPosX - (CurrentPosX + 2.f));
	      if (i == 0) Trigger = true;
	      i--;
	    } else {
	      shape.SetTransformX(CurrentPosX);
	      if (i == 200) Trigger = false;
	      i++;
	    }
	}
	
        window.clear();
        window.draw(shape.GetShape());
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
}

/*
class clsTransform
{
private:
  float m_PosX = 0.f, m_PosY = 0.f, m_Gravity = 0.f;
  float m_Width = 0.f, m_Height = 0.f;
  
public:
  clsTransform()
  {
  }

  clsTransform(float PosX, float PosY, float Width, float Height, float Gravity=0.f)
    : m_PosX(PosX), m_PosY(PosY), m_Gravity(Gravity), m_Width(Width), m_Height(Height)
  {
  }

  void SetWidth(const float &Width)
  {
    this->m_Width = Width;
  }

  float GetWidth() const
  {
    return (this->m_Width);
  }
  
  void SetHeight(const float &Height)
  {
    this->m_Height = Height;
  }

  float GetHeight() const
  {
    return (this->m_Height);
  }

  void SetGravity(const float &Gravity)
  {
    m_Gravity = Gravity;
  }

  float GetGravity() const
  {
    return (m_Gravity);
  }

  void SetPosX(const float &PosX)
  {
    this->m_PosX += PosX;
  }

  void SetPosY(const float &PosY)
  {
    this->m_PosY += PosY;
  }

  void SetPosXY(const float &PosX, const float &PosY)
  {
    this->m_PosX += PosX;
    this->m_PosY += PosY;
  }
  
  float GetPosX() const
  {
    return (m_PosX);
  }

  float GetPosY() const
  {
    return (m_PosY);
  }

  void SetDefaultPos(const float &PosX, const float &PosY)
  {
    this->m_PosX = PosX;
    this->m_PosY = PosY;
  }
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
  clsCShape()
  {
  }

  clsCShape(char ShapeType, uint16_t Clr[5], float PosX, float PosY, float Width, float Height, float Gravity=0.f)
    : clsTransform(PosX, PosY, Width, Height, Gravity), m_Shape(nullptr), m_Color(nullptr), m_CTransform(nullptr)
  {
    m_CTransform = new clsTransform(PosX, PosY, Width, Height, Gravity);
    SetShape(ShapeType);
    *m_Shape = GetShape();
    Clr[4] == 0 ? SetColor() : SetColor(Clr);
    *m_Color = GetColor();
    //m_Shape->setFillColor(*m_Color);
    SetShapeColor(*m_Color);
    SetInitPos(m_CTransform->GetPosX(), m_CTransform->GetPosY());
  }

  void SetShape(char ShapeType)
  {
    switch (ShapeType) {
    case (enShapeTypes::Rectangle):
      m_Shape = new sf::RectangleShape({clsTransform::GetWidth(), clsTransform::GetHeight()});
      break;
    case (enShapeTypes::Circle):
      m_Shape = new sf::CircleShape(clsTransform::GetWidth());
      break;
    case (enShapeTypes::Triangle):
      m_Shape = new sf::CircleShape(clsTransform::GetWidth(), 2);
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
  
  void SetColor(const uint16_t Clr[5])
  {
    m_Color = new sf::Color(Clr[0], Clr[1], Clr[2], Clr[3]);
  }
  
  void SetColor()
  {
    m_Color = new sf::Color(sf::Color::Red);
  }

  void SetColor(const sf::Color &Color)
  {
    m_Color = new sf::Color(Color);
  }

  void SetShapeColor(const sf::Color &Color)
  {
    m_Shape->setFillColor(Color);
  }

  sf::Shape &GetShape() const
  {
    return (*m_Shape);
  }

  sf::Color &GetColor() const
  {
    return (*m_Color);
  }

  sf::Color &GetShapeColor() const
  {
    return (*m_Color);
  }

  void SetInitPos(const float &PosX, const float &PosY)
  {
    m_CTransform->SetDefaultPos(PosX, PosY);
    GetShape().setPosition({m_CTransform->GetPosX(), m_CTransform->GetPosY()});
  }
  
  void SetTransformX(const float &PosX)
  {
    m_CTransform->SetPosX(PosX);
    GetShape().setPosition({m_CTransform->GetPosX(),  m_CTransform->GetPosY()});
  }

  void SetTransformY(const float &PosY)
  {
    m_CTransform->SetPosY(PosY);
    GetShape().setPosition({m_CTransform->GetPosX(),  m_CTransform->GetPosY()});
  }

  void SetTransformXY(const float &PosX, const float &PosY)
  {
    m_CTransform->SetPosX(PosX);
    m_CTransform->SetPosY(PosY);
    GetShape().setPosition({m_CTransform->GetPosX(),  m_CTransform->GetPosY()});
  }
 
  void SetDefaultPos(float PosX, float PosY)
  {
    m_CTransform->SetDefaultPos(PosX, PosY);
    SetInitPos(m_CTransform->GetPosX(), m_CTransform->GetPosY());
  }
  //std::cout<<m_CTransform->GetPosX()<<" | "<<m_CTransform->GetPosY()<<'\n';
  //std::cout<<clsTransform::GetPosX()<<" | "<<clsTransform::GetPosY()<<'\n';  
  ~clsCShape()
  {
    if (m_Shape != nullptr)
      delete m_Shape;

    if (m_Color != nullptr)
      delete m_Color;

    if (m_CTransform != nullptr)
      delete [] m_CTransform;
  }
};
*/
/*
int main() {
    sf::RenderWindow window(sf::VideoMode({1200, 600}), "Project X - 2D Engine");
    window.setFramerateLimit(60);
    (void) ImGui::SFML::Init(window);
    ImGui::LoadIniSettingsFromDisk("imgui.ini");
    ImGui::SetNextWindowPos(ImVec2(850, 0));
    sf::Shape *Shape = nullptr;
    sf::Color *Clr = nullptr;
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);
    Shape = new sf::CircleShape(100.f);
    Clr = new sf::Color(150, 150, 150, 255);
    Shape->setFillColor(*Clr);
    sf::Clock deltaClock;

    char ShapeC = 'c';
    uint16_t i = 1, j = 1, tracking = j, shapeCount = 0;
    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        //ImGui::ShowDemoWindow();
	ImGui::SetNextWindowSize(ImVec2(350, 600));
        //ImGui::Begin("World Edito", &opened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
	ImGui::Begin("##CustomWindow", &opened, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse);

	// Calculate centered position for the title text
	float windowWidth = ImGui::GetWindowWidth();
	float textWidth   = ImGui::CalcTextSize("World Editor").x;
	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);


	// Render the title text
	ImGui::Text("World Editor");
	float PosX = i * 5.0f, PosY = PosX, fSlider = 0, rl = -10, rr = 10;
	uint16_t R = i * 2 * j, G = 4 * j * i, B = j + i * j + 5;
        if (ImGui::Button("Move")) i++;
	else if (ImGui::Button("Random Color")) j += 2;
	else if (ImGui::Button("Reset")) {
	  Shape = new sf::CircleShape(100.f);
	  Shape->setPosition({0.f, 0.f});
	  Shape->setFillColor(*Clr);
	  i = 1;
	  j = 1;
	  tracking = j;
	  shapeCount = 0;
	} else if (ImGui::Button("Change shape")) {
	  switch (shapeCount) {
	  case (0):
	    Shape = new sf::RectangleShape({200.f, 100.f});
	    Shape->setFillColor(*Clr);
	    ShapeC = 'r';
	    break;
	  case (1):
	    Shape = new sf::CircleShape(100.f, 3.f);
	    Shape->setFillColor(*Clr);
	    ShapeC = 't';
	    break;
	  case (2):
	    Shape = new sf::CircleShape(100.f, 4);
	    Shape->setFillColor(*Clr);
	    ShapeC = 'p';
	    break;
	  case (3):
	    Shape = new sf::CircleShape(100.f, 6);
	    Shape->setFillColor(*Clr);
	    ShapeC = 'h';
	    break;
	  case (4):
	    Shape = new sf::CircleShape(100.f, 8);
	    Shape->setFillColor(*Clr);
	    ShapeC = 'o';
	    break;
	  case (5):
	    Shape = new sf::RectangleShape({200.f, 200.f});
	    Shape->setFillColor(*Clr);

	    ShapeC = 's';
	    break;
	  }
	  shapeCount++;
	} else if (ImGui::SliderFloat("Size", &fSlider, rl, rr)) {
	  std::cout<<ShapeC<<'\n';
	  if (ShapeC == 's') {
	    Shape = new sf::RectangleShape({rr, rr});
	    //Shape->setPosition({rr, rr});
	  }
	}
	if (tracking < j) {
	  Clr = new sf::Color(R, G, B, 255);
	  Shape->setFillColor(*Clr);
	  tracking = j;
	}
	if (shapeCount > 5) shapeCount = 0;
        Shape->setPosition({PosX, PosY});

        ImGui::End();

        window.clear();
        window.draw(*Shape);
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
}
*/

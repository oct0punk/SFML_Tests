#include <SFML/Graphics.hpp>
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"
#include <iostream>

using namespace sf;
int main()
{    
    RenderWindow window(VideoMode(999, 666), "SFML works!");
    
    Texture texture;
    if (!texture.loadFromFile("Arts/Weed.png"))
        printf("Y veux pas charger la texture");

    Shader shader;
    shader.setUniform("texture", Shader::CurrentTexture);
    if (!shader.loadFromFile("Shaders/Noise.frag", Shader::Fragment))
        printf("Y veut pas charger le frag ");

    CircleShape spr(100.0f);
    spr.setOrigin(100.0f, 100.0f);
    spr.setPosition((Vector2f)window.getSize() * .5f);
    spr.setFillColor(Color::White);
    spr.setTexture(&texture);

    float color[3];
    float distance = .01f;

    ImGui::SFML::Init(window);
    Clock clock;
       
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == Event::Closed)
                window.close();
        }
        ImGui::SFML::Update(window, clock.restart());
        ImGui::Begin("Shader");
        if (ImGui::ColorPicker3("Dissolve Color", color))
            shader.setUniform("dissolveColor", Glsl::Vec4(color[0], color[1], color[2], 1.0f));
        
        if (ImGui::SliderFloat("Dissolve", &distance, 0.00002f, 1.0f))
            shader.setUniform("distance", distance);
        ImGui::End();
        
        window.clear();
        window.draw(spr, &shader);
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}
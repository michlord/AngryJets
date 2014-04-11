#include <iostream>
#include <SFML/Graphics.hpp>

#include "../../Engine/GuiWindow.h"
#include "../../Engine/GuiLabel.h"
#include "../../Engine/GuiHighlightedLabel.h"
#include "../../Engine/GuiVerticalLayout.h"
#include "../../Engine/GuiHorizontalLayout.h"
#include "../../Engine/ResourceManager.h"

#include <tuple>
#include <sigslot.h>


void loadResources(){
    engine::ResourceManager::resources_list_t resources_list;
    std::string directory = "C:/Dev/AngryJets/Tests/ResourceManagerTest/Resources/";
    resources_list.push_back(std::make_tuple("font",directory+"font.ttf",engine::ResourceManager::resource_type::FONT));
    engine::rm->batchLoadResources(resources_list);
}




class Runner : public sigslot::has_slots<> {

public:
    void init(){
        loadResources();
        window = new sf::RenderWindow(sf::VideoMode(800, 600), "Gui test");
        gui_window = new engine::GuiWindow(*window);
        label = new engine::GuiLabel("Text",&engine::rm->getFont("font"));
        engine::GuiLabel  *label2,*label3,*label4;
        label2 = new engine::GuiLabel("Text2",&engine::rm->getFont("font"));
        label3 = new engine::GuiLabel("Text3",&engine::rm->getFont("font"));
        label4 = new engine::GuiLabel("Text4",&engine::rm->getFont("font"));

        //gui_window->setChild(label);


        vertical_layout = new engine::GuiVerticalLayout();
        gui_window->setChild(vertical_layout);

        vertical_layout->addChild(label);
        label->setAlignment(engine::GuiLabel::alignment::CENTER);
        label->setFontSize(40);
        label->setColor(sf::Color::Yellow);
        label->clicked.connect(this,&Runner::onClickedLabel);
        vertical_layout->addChild(label2);
        vertical_layout->addChild(label3);
        vertical_layout->addChild(label4);

        engine::GuiHorizontalLayout* horizontal_layout = new engine::GuiHorizontalLayout();
        vertical_layout->addChild(horizontal_layout);
        engine::GuiLabel  *label5,*label6,*label7;
        label5 = new engine::GuiLabel("Text5",&engine::rm->getFont("font"));
        label6 = new engine::GuiLabel("Text6",&engine::rm->getFont("font"));
        label7 = new engine::GuiLabel("Text7",&engine::rm->getFont("font"));
        horizontal_layout->addChild(label5);
        horizontal_layout->addChild(label6);
        horizontal_layout->addChild(label7);
        engine::GuiHighlightedLabel *highlighted_label = new engine::GuiHighlightedLabel("Text7",&engine::rm->getFont("font"),sf::Color::White,sf::Color::Red);
        horizontal_layout->addChild(highlighted_label);

        engine::GuiVerticalLayout* vert = new engine::GuiVerticalLayout();
        horizontal_layout->addChild(vert);
        engine::GuiHighlightedLabel *hl1 = new engine::GuiHighlightedLabel("Text8",&engine::rm->getFont("font"),sf::Color::White,sf::Color::Green);
        engine::GuiHighlightedLabel *hl2 = new engine::GuiHighlightedLabel("Text9",&engine::rm->getFont("font"),sf::Color::White,sf::Color::Green);
        engine::GuiHighlightedLabel *hl3 = new engine::GuiHighlightedLabel("Text10",&engine::rm->getFont("font"),sf::Color::White,sf::Color::Green);
        vert->addChild(hl1);
        vert->addChild(hl2);
        vert->addChild(hl3);

    }
    void run(){
        while (window->isOpen())
        {
            sf::Event event;
            while (window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window->close();
                gui_window->handleEvent(event);
            }
            window->clear();
            window->draw(*gui_window);
            window->display();
        }
    }

private:
    sf::RenderWindow*  window;
    engine::GuiWindow* gui_window;
    engine::GuiLabel*  label;

    engine::GuiVerticalLayout* vertical_layout;
    void onClickedLabel(){
        std::cout << "Indeed the label was clicked.\n";
    }
};


int main()
{
    Runner app;
    app.init();
    app.run();

    return 0;
}

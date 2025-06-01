//g++ main.cpp -o sfml-app -I/usr/include -L/usr/lib -lsfml-graphics -lsfml-window -lsfml-system
//this command compiles this file perfectly if you're using arch linux
//x86_64-w64-mingw32-g++ main.cpp -o my_program.exe -lsfml-graphics -lsfml-window -lsfml-system
//g++ ./main.cpp ../build/Matrix.o ../build/Neuralnetwork.o -Iinclude -L/usr/lib -lsfml-graphics -lsfml-window -lsfml-system -o ../bin/sanyi
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../include/NeuralNetwork.h"

class Square : public sf::RectangleShape
{
private:
    float s;
    int color = 255;
public:
    Square(float size = 100.0f, sf::Vector2f pos = sf::Vector2f(0, 0)): RectangleShape(sf::Vector2f(size,size)),s(size){
        setFillColor(sf::Color::White);
        setPosition(pos);
    }
    void setShade(sf::Vector2i cursor){
        //sets the darkness of the square with a percentage
        float d = getDistance(cursor);

        int temp = static_cast<int>(255 - 255*d);
        if(temp < color){
            color = temp;
            setFillColor(sf::Color(color,color,color));
        }
    }
    void setColor(int c)
    {
        color = c;
    }
    int getColor(){
        return color;
    }
private:
    float getDistance(sf::Vector2i c){ 
        //gets the distance from the middle of the square,
        // returns -1 if there are no effects, but if the
        // square should be over 60% dark returns that percentage
        sf::Vector2f center = getPosition() + sf::Vector2f(s / 2, s / 2);
        float x,y;
        x =(-1*abs(center.x - c.x)/s)+1;
        y =(-1*abs(center.y - c.y)/s)+1;
        const float p = 0.50;
        float value = (x+y)/2;
        if(value <= p)
            return -1;
        
        return value; //get the avarage
    }
    float abs(float a){
        if(a >= 0) return a;
        else return a*-1;
    }
};


class Table {
private:
    const int x_s, y_s; //size of the table
    const float size; //size of a square (pixels)
    const sf::Vector2f pos;
    std::vector<std::vector<Square>> data;
public:
    Table(int x, int y, float s, sf::Vector2f position): x_s(x), y_s(y), size(s), pos(position){
        data.assign(y_s, std::vector<Square>(x_s));
        for(int yi = 0; yi < y_s; yi++)
            for(int xi = 0; xi < x_s; xi++){
                sf::Vector2f shift(xi*size,yi*size);
                //this is a terrible way to do this but idc tbh
                //in the end this will happen only once when running
                sf::Vector2f temp = pos + shift;
                data[yi][xi] = Square(size,temp);
            }
    }
    void empty(){
        for(int y = 0; y < y_s; y++)
            for(int x = 0; x < x_s; x++){
                data[y][x].setColor(255);
                data[y][x].setFillColor(sf::Color::White);
            }
    }
    void draw(sf::RenderWindow& window){
        for(int y = 0; y < y_s; y++)
        {
            for(int x = 0; x < x_s; x++){
                window.draw(data[y][x]);
            }
        }
    }
    void modify(sf::Vector2i& mousePos){
        for(int y = 0; y < y_s; y++) //you don't need to go through every square but in this scale it's isn't a performance issue
        {
            for(int x = 0; x < x_s; x++){
                data[y][x].setShade(mousePos);
            }
        }
    }
    std::vector<double> getData(){
        //there are no need to return in double but I wrote the networks code with double so once again, I don't care
        std::vector<double> a;
        for(int y = 0; y < y_s; y++)
            for(int x = 0; x < x_s; x++)
                a.push_back(static_cast<double>(255-data[y][x].getColor()));
        return a;
    }
};

class Button : public sf::RectangleShape {
    public:
        Button(sf::Color color, sf::Vector2f size, sf::Vector2f pos, std::string text)
            : RectangleShape(size)
        {
            setFillColor(color);
            setPosition(pos);
            //I should add text to the buttons but i don't have a clue how to do that
        }
        bool isPressed(sf::Vector2i m){
            sf::FloatRect rectBounds = getGlobalBounds();
            if (rectBounds.contains(sf::Vector2f(static_cast<float>(m.x),static_cast<float>(m.y))))
                return true;
            else
                return false;
        }
};

bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(),"ArtInt Kiserletbazar 2025");

    Table t(8,8,100,sf::Vector2f(100.0f,100.0f));
    Button process(sf::Color::Green, sf::Vector2f(200,100),sf::Vector2f(1000,800),"számítás");
    Button clear(sf::Color::Red, sf::Vector2f(200,100),sf::Vector2f(1250,800),"törlés");
    /*
    std::ofstream myfile;
    
    int name = 0;
    std::string filename = "0.txt";
    while(fileExists(filename))
    {
        filename = std::to_string(name) + ".txt";
        name++;
    }
    myfile.open(filename);

    */
    bool click = 0; 
    /*
    CIRCLE
    CROSS
    TRIANGLE
    SMILEY
    */
    std::vector<sf::Texture> textures(4);
    std::vector<sf::Sprite> pic;
    try{
        textures[0].loadFromFile("./img/circle.jpg");
        textures[1].loadFromFile("./img/cross.jpg");
        textures[2].loadFromFile("./img/triangle.jpg");
        textures[3].loadFromFile("./img/smiley.jpg");
        pic.emplace_back(sf::Sprite(textures[0]));
        pic.emplace_back(sf::Sprite(textures[1]));
        pic.emplace_back(sf::Sprite(textures[2]));
        pic.emplace_back(sf::Sprite(textures[3]));
        for(int i = 0; i < 4; i++)
        {
            pic[i].setPosition(sf::Vector2f(1000,100));
        }
    }
    catch(const std::exception& e){
        std::cout << "Caught an error: " << e.what() << std::endl;
        return 1;
    }

    
    //std::srand(time(0));
    //rand()%4
    int obj_ind = 0;
    std::string path = "B.txt";
    NeuralNetwork sanyi(path);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent()) //events
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window); //sets changes
            t.modify(mousePos);

            if(click == 0)
            {
                if(clear.isPressed(mousePos))
                    t.empty();
                else if(process.isPressed(mousePos))
                {
                    //start neural network here
                    std::vector<double> d = t.getData();
                    int index = sanyi.run(d);
                    obj_ind = index;

                    /*
                    
                    std::vector<double> d = t.getData();
                    for(double number:d){
                        myfile << number << " ";
                    }
                    myfile << obj_ind;
                    myfile << "\n";
                    t.empty();
                    obj_ind = rand()%4;
                    */
                }
                click = 1;
            }
        }
        else
        {
            click = 0;
        }

        //clear
        window.clear();
        //draw
        t.draw(window);
        window.draw(process);
        window.draw(clear);
        window.draw(pic[obj_ind]);
        //display
        window.display();
    }
    return 0;
}
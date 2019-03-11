#include "SFML/Graphics.hpp"  
int main() {
sf::RenderWindow window(sf::VideoMode(400, 240), "Test Window");
window.setFramerateLimit(30);
sf::VertexArray pointmap(sf::Points, 400 * 10);
for(register int a = 0;a < 400 * 10;a++) {
    pointmap[a].position = sf::Vector2f(a % 400,a / 400);
    pointmap[a].color = sf::Color::Green;
}
while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
        window.close();
    }
    window.clear();
    window.draw(pointmap);
    //</debug>
    window.display();
}
return 0;

}
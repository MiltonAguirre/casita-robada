#ifndef INPUTTEXT_H
#define INPUTTEXT_H
#include <SFML/Graphics.hpp>
using namespace sf;
class InputText:public sf::Text {
	sf::Clock clock;
	std::string value;
	bool is_down[sf::Keyboard::KeyCount];
	void TestKey(sf::Keyboard::Key k, char c) {
		bool was_down=is_down[int(k)];
		is_down[int(k)]=sf::Keyboard::isKeyPressed(k);
		if (is_down[int(k)] && !was_down) value+=c;
	}
	unsigned int max_chars;
	bool editable;
	bool single_word;
public:
	InputText(const sf::Font &font, int size=30, sf::Color color=sf::Color::Black) {
		for(int i=0;i<sf::Keyboard::KeyCount;i++) is_down[i]=true;
		max_chars=0;
		single_word=false;
		editable=true;
		setFont(font);
		setCharacterSize(size);
		setColor(color);
		
	}
	bool processEvent(const sf::Event &event) {
		if (!editable) return false;
		if (event.type == sf::Event::TextEntered) {
			if (event.text.unicode=='\b') {
				if (value.size()) value.erase(value.size()-1,1);
			} else if (event.text.unicode>=32 && event.text.unicode<128) {
				if (!max_chars || value.size()<max_chars) 
					if (!single_word || event.text.unicode!=' ')
						value += static_cast<char>(event.text.unicode);
			}
			return true;
		}
		return false;
	}
	void setMaxChars(unsigned int max) { max_chars=max; }
	void update() {
		if (editable && int(clock.getElapsedTime().asSeconds()*3)%2)
			setString(value+"|");
		else 
			setString(value);
	}
	void setEditable(bool value) { editable=value; }
	void setSingleWord(bool value) { single_word=value; }
	std::string getValue() { return value; }
	void reset() { value.clear(); }
};

#endif

#ifndef LEVELGENERATOR_HPP_
#define LEVELGENERATOR_HPP_

#include <nlohmann/json.hpp>
#include "./Assets.hpp"

class LevelGenerator {
    public:
        LevelGenerator(std::string lvlname) {
            parseLvl(lvlname);
        };
        LevelGenerator() {};
        ~LevelGenerator() = default;

		std::vector<sf::Vector2f> add_to_vector(std::string line, std::vector<sf::Vector2f> vect) {
			int count = countCharacter(line, '(');

			for (int i = 0; i != count; i++) {
				int one = std::stoi(line.substr(findNOccur(line, '(', i + 1) + 1, line.size() - (line.size() - findNOccur(line, ',', i + 1) - 1)));
				int two = std::stoi(line.substr(findNOccur(line, ',', i + 1) + 1, line.size() - (line.size() - findNOccur(line, ')', i + 1) - 1)));
				vect.push_back(sf::Vector2f(one, two));
			}
			return vect;
		}
		
        bool parseLvl(std::string lvl_name) {
			std::string tmp;
			std::ifstream f(lvl_name);
			if (f.is_open()) {
				while (getline(f,tmp)) {
					for (int i = 0; i != tmp.size(); i++) {
						switch (tmp[i]) {
							case '{':
								_wall.push_back(add_to_vector(tmp, std::vector<sf::Vector2f>()));
								break;
							case '(':
								add_to_vector(tmp, _tile);
								break;
							case '[':
								add_to_vector(tmp, _bumper);
								break;
							default:
								break;
						}
					}
				}
			} else return false;
			return true;
        };
		std::vector<sf::ConvexShape> createWalls() {

        }
        std::vector<Sprite> createTiles() {
            
        }
        std::vector<sf::CircleShape> createBumpers() {
            
        }

    private:
		std::vector<std::vector<sf::Vector2f>> _wall;
		std::vector<sf::Vector2f> _bumper;
		std::vector<sf::Vector2f> _tile;
};

#endif /* !LEVELGENERATOR_HPP_ */

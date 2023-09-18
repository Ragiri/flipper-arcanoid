#ifndef LEVELGENERATOR_HPP_
#define LEVELGENERATOR_HPP_

#include <nlohmann/json.hpp>
#include "./Assets.hpp"

class LevelGenerator {
    public:
        LevelGenerator(std::string lvlname): _t(spriteAssets["Tile"]) {
            parseLvl(lvlname);
            _bumperTexture.loadFromFile(textureAssets["Bumper"]);
        };
        LevelGenerator(): _t(spriteAssets["Tile"]) {
            _bumperTexture.loadFromFile(textureAssets["Bumper"]);
        };
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
					switch (tmp[0]) {
						case '{':
							_wall.push_back(add_to_vector(tmp, std::vector<sf::Vector2f>()));
							break;
						case '(':
							_tile = add_to_vector(tmp.substr(1, tmp.size() - 2), _tile);
							break;
						case '[':
							_bumper = add_to_vector(tmp, _bumper);
							break;
						default:
							break;
					}
				}
			} else return false;
			return true;
        };


        void clearAll() {
            _wall.clear();
            _bumper.clear();
            _tile.clear();
        }
		std::vector<sf::ConvexShape> createWalls() {
            std::vector<sf::ConvexShape> res;

            for (auto &w: _wall) {
                sf::ConvexShape tmp(w.size());
                for (int i = 0; i != w.size(); i++)
                    tmp.setPoint(i, w[i]);
                tmp.setFillColor(sf::Color::White);
                res.push_back(tmp);
            }
            return res;
        }

        std::vector<Sprite> createTiles() {
            std::vector<Sprite> res;

            for (auto &t: _tile) {
                _t.setPosition(sf::Vector2f(t.x, t.y));
                res.push_back(_t);
            }
            return res;
        }

        std::vector<sf::CircleShape> createBumpers() {
            std::vector<sf::CircleShape> res;
            
            for (auto &b: _bumper) {
                int r = (std::rand() % (25 - 10 + 1)) + 5;
                sf::CircleShape tmp(r);
                tmp.setTexture(&_bumperTexture);
                tmp.setPosition(sf::Vector2f(b.x, b.y));
                res.push_back(tmp);
            }
            return res;
        }

    private:
        sf::Texture _bumperTexture;
		std::vector<std::vector<sf::Vector2f>> _wall;
		std::vector<sf::Vector2f> _bumper;
        Sprite _t;
		std::vector<sf::Vector2f> _tile;
};

#endif /* !LEVELGENERATOR_HPP_ */

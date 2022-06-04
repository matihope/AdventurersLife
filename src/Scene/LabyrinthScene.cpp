#include <Game/Game.hpp>
#include <Scene/LabyrinthScene.hpp>
#include <PlayerLabyrinth/Player.hpp>
#include <GameObj/GameObj.hpp>
#include <TileMap/TileMap.hpp>
#include <algorithm>

#include <vector>
#include <ctime>
#include <stack>
#include <list>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
class MazeSolver {
    private:
        int w, h;
        std::pair<int, int> start;
        std::pair<int, int> end;
        struct vert {
            bool visited = false;
            std::pair<int, int> parent = {-1, -1};
        };
        std::vector<std::vector<vert>> graph;
        std::vector<std::vector<int>> maze;
        std::vector<std::pair<int, int>> solved;

        int getId(const int& x, const int& y){
            return y * w + x;
        }

        std::pair<int, int> getXY(const int& id){
            return {id % w, id / h};
        }

        void getPath(const std::pair<int, int>& start, const std::pair<int, int>& pos){
            if(pos != start)
                getPath(start, graph[pos.first][pos.second].parent);
            solved.push_back(pos);
        }

        void m_solve() {
            std::stack<int> st;
            graph[start.first][start.second].visited = true;
            graph[start.first][start.second].parent = start;
            st.push(getId(start.first, start.second));
            while(!st.empty()) {
                int top = st.top(); st.pop();
                auto [x, y] = getXY(top);
                std::vector<std::pair<int, int>> neighs = {{x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}};
                for(auto [xn, yn]: neighs) {
                    if(0 <= xn && xn < w && 0 <= yn && yn < h) {
                        if(!graph[xn][yn].visited && maze[xn][yn] == 0){
                            graph[xn][yn].visited = true;
                            graph[xn][yn].parent = {x, y};
                            st.push(getId(xn, yn));
                        }
                    }
                }
            }
            getPath(start, end);
        }

    public:
        MazeSolver(std::pair<int, int> start, std::pair<int, int> end, std::vector<std::vector<int>> maze) {
            this->w = maze[0].size();
            this->h = maze.size();
            this->start = start;
            this->end = end;
            this->maze = maze;

            graph.assign(maze[0].size(), std::vector<vert>(maze.size()));
            m_solve();
        }

        const std::vector<std::pair<int, int>>& solve() const {
            return solved;
        }

};

class BtrMazeGen {
    std::vector<int> REP;
    int w, h;
    int start;
    int end;
    std::pair<int, int> startc;
    std::pair<int, int> endc;

    int Find(int a){
        if(REP[a] == a)
            return a;
        return REP[a] = Find(REP[a]);
    }

    void Union(int a, int b){
        REP[Find(b)] = Find(a);
    }

    int getId(const int& x, const int& y){
        return y * w + x;
    }

    std::pair<int, int> getXY(const int& id){
        return {id % w, id / h};
    }

    std::vector<std::vector<int>> wrap(std::vector<std::vector<int>>& in){
        std::vector<std::vector<int>> out;
        out.assign(in.size() + 1, std::vector<int>(in[0].size() + 1, 1));
        for(size_t i = 0; i < in.size(); ++i){
            for(size_t j = 0; j < in[0].size(); ++j){
                out[i + 1][j + 1] = in[i][j];
            }
        }
        return out;
    }

    public:
        BtrMazeGen(int width, int height) {
            if(w % 2)
                w--;
            if(h % 2)
                h--;
            w = width / 2;
            h = height / 2;
        }

        std::vector<std::vector<int>> gen() {
            struct Wall {
                int t1, t2;
                std::pair<int, int> coords = {-1, -1};
            };
            std::vector<Wall> walls;

            REP.assign(w * h, 0);
            std::vector<std::vector<int>> out(h * 2, std::vector<int>(w * 2, 1));
            for(int i = 0; i < w * h; ++i)
                REP[i] = i;

            out[0][0] = 0;
            for(int i = 0; i < w * h; ++i){
                auto [x, y] = getXY(i);
                if(x + 1 < w){
                    out[(x + 1) * 2][y * 2] = 0;
                    walls.push_back({i, getId(x + 1, y)});
                    walls.back().coords = {x * 2 + 1, y * 2};
                }
                if(y + 1 < h){
                    out[x * 2][(y + 1) * 2] = 0;
                    walls.push_back({i, getId(x, y + 1)});
                    walls.back().coords = {x * 2, y * 2 + 1};
                }
            }
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(walls.begin(), walls.end(), std::default_random_engine(seed));
            for(auto& w: walls){
                if(Find(w.t1) != Find(w.t2)) {
                    Union(w.t1, w.t2);
                    out[w.coords.first][w.coords.second] = 0;
                }
            }

            return wrap(out);
        }
};

void LabyrinthScene::draw(sf::RenderTarget& target) {
    Scene::draw(target);
    std::vector<std::shared_ptr<GameObj>> ySort;
    for(auto& p : getTiles())
        ySort.push_back(p);
    ySort.push_back(m_player);
    std::sort(ySort.begin(), ySort.end(), [&](const auto& a, const auto& b){
        return a->getPosition().y < b->getPosition().y;
    });
    for(auto& p: ySort) {
        target.draw(*p);
    }
}

std::shared_ptr<Tile> mkT(int tW, int tH, int x, int y, int wariant=0) {
    CollisionShape s;
    s.setShape({ {2.0f, 2.0f}, {14.0f, 2.f}, {14.0f, 14.0f}, {2.0f, 14.0f} });
    std::string texture_link = "../resources/Backgrounds/Tilesets/TilesetDungeon.png";

    auto t = std::make_shared<Tile>();
    t->setTexture(texture_link);
    t->setPosition(sf::Vector2f(x * 16, y * 16));
    if(wariant == 0)
        t->setTextureRect(sf::IntRect(0, 16 * 3, 16, 16));
    else
        t->setTextureRect(sf::IntRect(16, 16, 16, 16));
    t->setCollisionShape(s);
    return t;
}

void LabyrinthScene::load() {

    auto map = std::make_shared<TileMap>();
    if(!map->load("../worlds/shrek.json"))
        std::cout << "Could not load world.json. Make sure world is inside the worlds folder.\n";
    else{
        addUpdatable(map);
        sprites.addSprite(map, 0);
    }

    int w = 9, h = 9;
    std::vector<std::vector<int>> out;
    BtrMazeGen m(w, h);
    out = m.gen();
    for(int i = 0; i < w; ++i) {
        for(int j = 0; j < h; ++j){
            if(out[i][j]){
                m_tiles.push_back(mkT(w, h, j, i));
            }
            std::cout << out[i][j] << " ";
        }
        std::cout << '\n';
    }
    m_player = std::make_shared<PlayerL>();
    m_player->setPosition({16, 16});
    // sprites.addSprite(m_player, 1);
    addUpdatable(m_player);

    auto ans = MazeSolver({1, 1}, {w - 2, h - 2}, out).solve();
    for(auto& [x, y]: ans){
        sprites.addSprite(mkT(w, h, y, x, 1), 0);
    }

    auto zamek = std::make_shared<Tile>();
    zamek->setTexture("../resources/Backgrounds/Tilesets/TilesetElement.png");
    zamek->setPosition(sf::Vector2f((w - 2) * 16, (h - 2) * 16));
    zamek->setTextureRect(sf::IntRect(16 * 15, 0, 16, 16));
    m_tiles.push_back(zamek);
}

std::vector<std::shared_ptr<Tile>>& LabyrinthScene::getTiles() {
    return m_tiles;
}

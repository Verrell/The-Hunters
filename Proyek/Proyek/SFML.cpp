#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>

class Cobjek{
protected:
	sf::Texture _texture;
	sf::Sprite _sprite;
	sf::Vector2f _vector;
public:
	sf::Sprite drawsprite(){
		return _sprite;
	}
	sf::Vector2f getvector(){
		return _vector;
	}
};

class Cbow:public Cobjek{
private:
	float _distance, _angle;
public:
	Cbow(){
		_distance=0;
		_angle=0;
		_vector.x=400;
		_vector.y=450;
		_texture.loadFromFile("Bowdown.png", sf::IntRect(0,0,96,96));
		_sprite.setOrigin(48,48);
		_sprite.setTexture(_texture);
		_sprite.setPosition(_vector.x,_vector.y);
	}
	sf::Sprite set (float x, float y){
		_distance=sqrt(double((x-_vector.x)*(x-_vector.x)+(_vector.y-y)*(_vector.y-y)));
		_angle=asin(double((_vector.y-y)/(_distance)))/0.0175;
		if (x>_vector.x){
			_angle*=-1;
		}
		if (x<_vector.x){
			_angle+=180;
		}
		_angle-=90;
		_sprite.setRotation(_angle);
		return _sprite;
	}
};

class Carrow:public Cobjek{
private:
	float _vx, _vy, _speed, _distance, _angle;
public:
	Carrow(){
		_vector.x=412;
		_vector.y=450;
		_distance=0;
		_speed=10;
		_angle=0;
		_texture.loadFromFile("Arrow.png", sf::IntRect(0,0,32,32));
		_sprite.setTexture(_texture);
		_sprite.setPosition(_vector.x,_vector.y);
	}
	void set(float x, float y){
		_distance=sqrt(double((x-_vector.x)*(x-_vector.x)+(_vector.y-y)*(_vector.y-y)));
		_vx=(_speed*(x-_vector.x)/_distance);
		_vy=(_speed*(y-_vector.y)/_distance);
		_angle=asin(double((_vector.y-y)/(_distance)))/0.0175;
		if (x>_vector.x){
			_angle*=-1;
		}
		if (x<_vector.x){
			_angle+=180;
		}
		_angle-=90;
		_sprite.setRotation(_angle);
	}
	void move(){
		_vector.x+=_vx;
		_vector.y+=_vy;
		_sprite.setPosition(_vector.x,_vector.y);
	}
	bool check(){
		if (_vector.x<0 || _vector.x>800 || _vector.y<0 || _vector.y>600){
			return true;
		}else{
			return false;
		}
	}
};

class Cpower{
protected:
	sf::Texture _texture;
	sf::Sprite _sprite;
	sf::Vector2f _vector;
	int _dx, _type;
public:
	Cpower(int x=0, int y=0){
		_vector.x=x;
		_vector.y=y;
		if (x==0){
			_dx=3;
		}else{
			_dx=-3;
		}
		_texture.loadFromFile("Test.jpg", sf::IntRect(0,0,32,32));
		_sprite.setTexture(_texture);
		_sprite.setPosition(_vector.x,_vector.y);
		_type=0;
	}
	virtual void move(){
		_vector.x+=_dx;
		_sprite.setPosition(_vector.x,_vector.y);
	}
	sf::Sprite drawsprite(){
		return _sprite;
	}
	bool checkcollision(sf::Vector2f v){
		if ((v.x>=_vector.x && v.x<=_vector.x+32) && (v.y>=_vector.y && v.y<=_vector.y+32)){
			return true;
		}else{
			return false;
		}
	}
	bool check(){
		if (_vector.x<0 || _vector.x>800 || _vector.y<0 || _vector.y>600){
			return true;
		}else{
			return false;
		}
	}
	int gettype(){
		return _type;
	}
};

class Cfreeze:public Cpower{
public:
	Cfreeze(int x=0, int y=0):Cpower(x,y){
		_texture.loadFromFile("Freeze.png", sf::IntRect(0,0,32,32));
		_sprite.setTexture(_texture);
		_type=1;
	}
	void move(){
		if (_vector.x==450){
			if (_dx>0){
				_dx=-3;
			}else{
				_dx=3;
			}
		}
		_vector.x+=_dx;
		_sprite.setPosition(_vector.x,_vector.y);
	}
};

class Cdouble:public Cpower{
public:
	Cdouble(int x=0, int y=0):Cpower(x,y){
		_texture.loadFromFile("Doublescore.png", sf::IntRect(0,0,32,32));
		_sprite.setTexture(_texture);
		_type=2;
	}
};

class Czap:public Cpower{
public:
	Czap(int x=0, int y=0):Cpower(x,y){
		_texture.loadFromFile("Zap.png", sf::IntRect(0,0,32,32));
		_sprite.setTexture(_texture);
		_type=3;
	}
	void move(){
		if (_vector.x==450){
			_dx*=2;
		}
		_vector.x+=_dx;
		_sprite.setPosition(_vector.x,_vector.y);
	}
};

class Czombirds{
protected:
	sf::Texture _texture;
	sf::Sprite _sprite;
	sf::Vector2f _vector;
	int _x, _y, _dx;
public:
	Czombirds(int x=0, int y=0){
		_vector.x=x;
		_vector.y=y;
		if (x==0){
			_dx=5;
		}else{
			_dx=-5;
		}
		updatesprite();
	}
	virtual void updatesprite(){
		if (_dx==5){
			_x=0;
		}else{
			_x=1;
		}
		_y=0;
		_texture.loadFromFile("Bird1.png", sf::IntRect(_x*64,_y*64,64,64));
		_sprite.setTexture(_texture);
		_sprite.setPosition(_vector.x,_vector.y);
	}
	sf::Sprite drawsprite(){
		return _sprite;
	}
	sf::Vector2f getvector(){
		return _vector;
	}
	void setcolorfreeze(){
		_sprite.setColor(sf::Color::Blue);
	}
	void setcolor(){
		_sprite.setColor(sf::Color::White);
	}
	bool check(){
		if (_vector.x<0 || _vector.x>800 || _vector.y<0 || _vector.y>600){
			return true;
		}else{
			return false;
		}
	}
	virtual void move(){
		_vector.x+=_dx;
		if (_y<2){
			_y+=1;
		}else if(_y==2){
			_y=0;
		}
		_texture.loadFromFile("Bird1.png", sf::IntRect(_x*64,_y*64,64,64));
		_sprite.setTexture(_texture);
		_sprite.setPosition(_vector.x,_vector.y);
	}
	bool checkcollision(sf::Vector2f v){
		if ((v.x>=_vector.x && v.x<=_vector.x+64) && (v.y>=_vector.y && v.y<=_vector.y+64)){
			return true;
		}else{
			return false;
		}
	}
};

class Czombirdsspeed:public Czombirds{
public:
	Czombirdsspeed(int x=0, int y=0):Czombirds(x,y){
		updatesprite();
	}
	void move(){
		if(_vector.x==400){
			_dx*=3;
		}
		if (_y==1){
			if (_x<2){
				_x+=1;
			}else if (_x==2){
				_x=0;
			}
		}else{
			if (_x>0){
				_x-=1;
			}else if (_x==0){
				_x=2;
			}
		}
		_vector.x+=_dx;
		_texture.loadFromFile("Bird2.png", sf::IntRect(_x*64,_y*64,64,64));
		_sprite.setTexture(_texture);
		_sprite.setPosition(_vector.x,_vector.y);
	}
	void updatesprite(){
		if (_dx>0){
			_x=2;
			_y=2;
		}else{
			_x=0;
			_y=1;
		}
		_texture.loadFromFile("Bird2.png", sf::IntRect(_x*64,_y*64,64,64));
		_sprite.setTexture(_texture);
		_sprite.setPosition(_vector.x,_vector.y);
	}
};

class Czombirdsback:public Czombirds{
public:
	Czombirdsback(int x=0, int y=0):Czombirds(x,y){
		updatesprite();
	}
	void move(){
		if(_vector.x==400){
			if(_dx<0){
				_dx=5;
				_x=4;
				_y=1;
			}else{
				_dx=-5;
				_x=0;
				_y=0;
			}
		}
		if (_y==0){
			if (_x<4){
				_x+=1;
			}else if (_x==4){
				_x=0;
			}
		}else{
			if (_x>0){
				_x-=1;
			}else if (_x==0){
				_x=4;
			}
		}
		_vector.x+=_dx;
		_texture.loadFromFile("Bird3.png", sf::IntRect(_x*64,_y*64,64,64));
		_sprite.setTexture(_texture);
		_sprite.setPosition(_vector.x,_vector.y);
	}
	void updatesprite(){
		if (_dx>0){
			_x=4;
			_y=1;
		}else{
			_x=0;
			_y=0;
		}
		_texture.loadFromFile("Bird3.png", sf::IntRect(_x*64,_y*64,64,64));
		_sprite.setTexture(_texture);
		_sprite.setPosition(_vector.x,_vector.y);
	}
};

class Czombirdszigzag:public Czombirds{
private:
	int _dy, _countx, _county;
public:
	Czombirdszigzag(int x=0, int y=0, int dy=0):Czombirds(x, y){
		_dy=dy;
		_countx=5;
		_county=0;
		updatesprite();
	}
	void move(){
		if (_county==0){
			_vector.x+=_dx;
			_sprite.setPosition(_vector.x,_vector.y);
			_countx--;
			if(_countx==0){
				_county=5;
			}
		}
		if(_countx==0){
			_vector.y+=_dy;
			_sprite.setPosition(_vector.x,_vector.y);
			_county--;
			if(_county==0){
				if(_dy==10){
					_dy=-10;
				}else{
					_dy=10;
				}
				_countx=5;
			}
		}
		if (_x>0){
			_x-=1;
		}else if (_x==0){
			_x=3;
		}
		_texture.loadFromFile("Bird4.png", sf::IntRect(_x*64,_y*64,64,64));
		_sprite.setTexture(_texture);
	}
	void updatesprite(){
		if (_dx>0){
			_x=3;
			_y=1;
		}else{
			_x=3;
			_y=0;
		}
		_texture.loadFromFile("Bird4.png", sf::IntRect(_x*64,_y*64,64,64));
		_sprite.setTexture(_texture);
		_sprite.setPosition(_vector.x,_vector.y);
	}
};

class Cmenu{
private:
	sf::Texture _targettexture;
	sf::Sprite _targetsprite;
	sf::Texture _bgtexture;
	sf::Sprite _bgsprite;
	sf::Texture _bgplaytexture;
	sf::Sprite _bgplaysprite;
	sf::Texture _bghstexture;
	sf::Sprite _bghssprite;
	sf::Texture _bgovertexture;
	sf::Sprite _bgoversprite;
	sf::Texture _titletexture;
	sf::Sprite _titlesprite;
	sf::Vector2f _titlevector;
	sf::Texture _playtexture;
	sf::Sprite _playsprite;
	sf::Vector2f _playvector;
	sf::Texture _hstexture;
	sf::Sprite _hssprite;
	sf::Vector2f _hsvector;
	sf::Texture _exittexture;
	sf::Sprite _exitsprite;
	sf::Vector2f _exitvector;
	sf::Texture _pooftexture;
	sf::Sprite _poofsprite;
	sf::Vector2f _poofvector;
public:
	Cmenu(){
		_titlevector.x=100;
		_titlevector.y=0;
		_playvector.x=200;
		_playvector.y=300;
		_hsvector.x=350;
		_hsvector.y=300;
		_exitvector.x=500;
		_exitvector.y=300;
		_targettexture.loadFromFile("Target.png", sf::IntRect(0,0,32,32));
		_targetsprite.setTexture(_targettexture);
		_bgtexture.loadFromFile("Background.png", sf::IntRect(0,0,800,600));
		_bgsprite.setTexture(_bgtexture);
		_bgplaytexture.loadFromFile("Bgplay.png", sf::IntRect(0,0,800,600));
		_bgplaysprite.setTexture(_bgplaytexture);
		_bghstexture.loadFromFile("Bghs.jpg", sf::IntRect(0,0,800,600));
		_bghssprite.setTexture(_bghstexture);
		_bgovertexture.loadFromFile("Bggo.png", sf::IntRect(0,0,800,600));
		_bgoversprite.setTexture(_bgovertexture);
		_titletexture.loadFromFile("Title.png", sf::IntRect(0,0,600,225));
		_titlesprite.setTexture(_titletexture);
		_titlesprite.setPosition(_titlevector.x,_titlevector.y);
		_playtexture.loadFromFile("Play.png", sf::IntRect(0,0,100,100));
		_playsprite.setTexture(_playtexture);
		_playsprite.setPosition(_playvector.x,_playvector.y);
		_hstexture.loadFromFile("Highscore.png", sf::IntRect(0,0,100,100));
		_hssprite.setTexture(_hstexture);
		_hssprite.setPosition(_hsvector.x,_hsvector.y);
		_exittexture.loadFromFile("Exit.png", sf::IntRect(0,0,100,100));
		_exitsprite.setTexture(_exittexture);
		_exitsprite.setPosition(_exitvector.x,_exitvector.y);
		_pooftexture.loadFromFile("Poof.png", sf::IntRect(0,0,85,64));
		_poofsprite.setTexture(_pooftexture);
	}
	sf::Sprite drawtargetsprite(float x, float y){
		_targetsprite.setPosition(x, y);
		return _targetsprite;
	}
	sf::Sprite drawbgsprite(){
		return _bgsprite;
	}
	sf::Sprite drawbgplaysprite(){
		return _bgplaysprite;
	}
	sf::Sprite drawbghssprite(){
		return _bghssprite;
	}
	sf::Sprite drawbgoversprite(){
		return _bgoversprite;
	}
	sf::Sprite drawtitlesprite(){
		return _titlesprite;
	}
	sf::Sprite drawplaysprite(){
		return _playsprite;
	}
	sf::Sprite drawhssprite(){
		return _hssprite;
	}
	sf::Sprite drawexitsprite(){
		return _exitsprite;
	}
	sf::Sprite drawpoofsprite(sf::Vector2f vector){
		_poofsprite.setPosition(vector.x,vector.y);
		return _poofsprite;
	}
	int set(float x, float y, int check){
		if((x>=_playvector.x && x<=_playvector.x+100) && (y>=_playvector.y && y<=_playvector.y+100) && check==0){
			return 1;
		}else if((x>=_hsvector.x && x<=_hsvector.x+100) && (y>=_hsvector.y && y<=_hsvector.y+100) && check==0){
			return 2;
		}else if((x>=_exitvector.x && x<=_exitvector.x+100) && (y>=_exitvector.y && y<=_exitvector.y+100) && check==0){
			return 3;
		}else if ((x>=249 && x<=536) && (y>=439 && y<=483) && check==2){
			return 0;
		}else if ((x>=285 && x<=546) && (y>=319 && y<=367) && check==4){
			return 0;
		}else{
			return check;
		}
	}
};

class Cgame{
private:
	sf::RenderWindow _window;
	std::stringstream _jumlahscore, _jumlaharrow, _jumlahlife;
	sf::Font _fontplay;
	sf::Text _textscore, _textarrow, _textlife;
	sf::Clock _clock;
	sf::Time _time;
	sf::SoundBuffer _soundbufferarrow;
	sf::Sound _soundarrow;
	sf::SoundBuffer _soundbufferbird;
	sf::Sound _soundbird;
	sf::Music _musicbg;
	Cmenu _menu;
	Cbow _bow;
	std::vector<Czombirds*> _obj;
	std::vector<Carrow*> _arrow;
	std::vector<Cpower*> _power;
	int _timecount, _rand, _score, _powertype, _powerspawntime, _checkplay, _checkdeath;
public:
	Cgame():_window(sf::VideoMode(800,600),"The Hunters"){
		_window.setFramerateLimit(30);
		_window.setMouseCursorVisible(false);
		_soundbufferarrow.loadFromFile("arrowmusic.wav");
		_soundarrow.setBuffer(_soundbufferarrow);
		_soundbufferbird.loadFromFile("birdmusic.wav");
		_soundbird.setBuffer(_soundbufferbird);
		_musicbg.openFromFile("bgmusic.wav");
		_fontplay.loadFromFile("upheaval.ttf");
		_textscore.setFont(_fontplay);
		_textscore.setCharacterSize(30);
		_textscore.setPosition(174,507);
		_textarrow.setFont(_fontplay);
		_textarrow.setCharacterSize(30);
		_textarrow.setPosition(498,530);
		_textlife.setFont(_fontplay);
		_textlife.setCharacterSize(30);
		_textlife.setPosition(174,550);
		_timecount=0;
		_score=0;
		_powertype=0;
		_powerspawntime=0;
		_checkplay=0;
		_checkdeath=5;
	}
	void play(){
		srand(time(0));
		_musicbg.play();
		_musicbg.setLoop(true);
		while (_window.isOpen()){
			sf::Event Event;
			while (_window.pollEvent(Event)){
				if (Event.type==sf::Event::Closed){
					_window.close();
				}
				if (Event.type==sf::Event::MouseButtonPressed){
					if (_checkplay==1){
						if (_arrow.size()<3){
							_arrow.push_back(new Carrow);
							_arrow[_arrow.size()-1]->set(Event.mouseButton.x,Event.mouseButton.y);
							_soundarrow.play();
						}
					}else if (_checkplay==0){
						_checkplay=_menu.set(Event.mouseButton.x,Event.mouseButton.y, _checkplay);
						if (_checkplay==1){
							_clock.restart();
						}
					}else if (_checkplay==2){
						_checkplay=_menu.set(Event.mouseButton.x,Event.mouseButton.y, _checkplay);
					}else if (_checkplay==4){
						_checkplay=_menu.set(Event.mouseButton.x,Event.mouseButton.y, _checkplay);
					}
				}
				if (Event.type==sf::Event::MouseMoved){
					std::cout<<"x:"<<Event.mouseMove.x<<"y :"<<Event.mouseMove.y<<std::endl;
				}
			}
			_window.clear();
			if (_checkplay==0){
				_window.draw(_menu.drawbgsprite());
				_window.draw(_menu.drawtitlesprite());
				_window.draw(_menu.drawplaysprite());
				_window.draw(_menu.drawhssprite());
				_window.draw(_menu.drawexitsprite());
			}else if (_checkplay==1 && _checkdeath>0){
				_window.draw(_menu.drawbgplaysprite());
				_window.draw(_bow.drawsprite());
				_time=_clock.getElapsedTime();
				_timecount=_time.asSeconds();
				if (_timecount==3){
					_powerspawntime+=1;
					if (_powertype==1){
						if (_powerspawntime==2){
							_powertype=0;
							_powerspawntime=0;
						}
					}else if (_powertype==2){
						if (_powerspawntime==5){
							_powertype=0;
							_powerspawntime=0;
						}
					}
					_clock.restart();
					if (_powertype!=1){
						spawner();
					}
				}
				if (_powerspawntime%2==0 && _powerspawntime>0 && _power.size()==0){
					spawnpower();
				}
				for (int i=0; i<_obj.size(); i++){
					if (_powertype==1){
						_obj[i]->setcolorfreeze();
					}else{
						_obj[i]->setcolor();
					}
					_window.draw(_obj[i]->drawsprite());
					if (_powertype!=1){
						_obj[i]->move();
						if (_obj[i]->check()){
							_obj.erase(_obj.begin()+i);
							_checkdeath-=1;
						}
					}
				}
				for (int i=0; i<_arrow.size(); i++){
					_window.draw(_arrow[i]->drawsprite());
					_arrow[i]->move();
					if (_arrow[i]->check()){
						_arrow.erase(_arrow.begin()+i);
					}
				}
				for (int i=0; i<_power.size(); i++){
					_window.draw(_power[i]->drawsprite());
					_power[i]->move();
					if (_power[i]->check()){
						_power.erase(_power.begin()+i);
						_powerspawntime=0;
					}
				}
				checkobj();
				checkpower();
				_jumlahscore.str(std::string());
				_jumlahscore<<_score;
				_jumlaharrow.str(std::string());
				_jumlaharrow<<(3-_arrow.size());
				_jumlahlife.str(std::string());
				_jumlahlife<<_checkdeath;
				_textscore.setString(_jumlahscore.str());
				_textarrow.setString(_jumlaharrow.str());
				_textlife.setString(_jumlahlife.str());
				_window.draw(_textarrow);
				_window.draw(_bow.set(sf::Mouse::getPosition(_window).x,sf::Mouse::getPosition(_window).y));
				_window.draw(_textscore);
				_window.draw(_textlife);
			}else if (_checkplay==2){
				_window.draw(_menu.drawbghssprite());
				loadhs("Game.txt");
			}else if (_checkplay==3){
				_window.close();
			}else if (_checkdeath==0){
				savehs("Game.txt",_score);
				_checkplay=4;
				_checkdeath=5;
				_score=0;
				_obj.clear();
				_arrow.clear();
				_power.clear();
			}else if (_checkplay==4){
				_window.draw(_menu.drawbgoversprite());
			}
			_window.draw(_menu.drawtargetsprite(sf::Mouse::getPosition(_window).x-32,sf::Mouse::getPosition(_window).y-32));
			_window.display();
		}
	}
	void spawner(){
		_rand=rand()%4+1;
		if (_rand==1){
			_obj.push_back(new Czombirds (rand()%2==0?0:800, rand()%101+50));
		}else if (_rand==2){
			_obj.push_back(new Czombirdsspeed (rand()%2==0?0:800, rand()%101+50));
		}else if (_rand==3){
			_obj.push_back(new Czombirdsback (rand()%2==0?0:800, rand()%101+50));
		}else{
			_obj.push_back(new Czombirdszigzag (rand()%2==0?0:800, rand()%101+50, rand()%2==0?10:-10));
		}
	}
	void spawnpower(){
		_rand=rand()%3+1;
		if (_rand==1){
			_power.push_back(new Cfreeze(rand()%2==0?0:800, rand()%50+1));
		}else if (_rand==2){
			_power.push_back(new Cdouble(rand()%2==0?0:800, rand()%50+1));
		}else{
			_power.push_back(new Czap(rand()%2==0?0:800, rand()%50+1));
		}
	}
	void checkobj(){
		for (int i=0; i<_arrow.size(); i++){
			for (int j=0; j<_obj.size(); j++){
				if(_obj[j]->checkcollision(_arrow[i]->getvector())){
					_window.draw(_menu.drawpoofsprite(_obj[j]->getvector()));
					_arrow.erase(_arrow.begin()+i);
					_obj.erase(_obj.begin()+j);
					_soundbird.play();
					if (_powertype==2){
						_score+=200;
					}else{
						_score+=100;
					}
					break;
				}
			}
		}
	}
	void checkpower(){
		for (int i=0; i<_arrow.size(); i++){
			for (int j=0; j<_power.size(); j++){
				if(_power[j]->checkcollision(_arrow[i]->getvector())){
					_powertype=_power[j]->gettype();
					if (_powertype==3){
						_score+=100*_obj.size();
						_obj.clear();
					}
					_arrow.erase(_arrow.begin()+i);
					_power.erase(_power.begin()+j);
					_powerspawntime=0;
					_clock.restart();
					break;
				}
			}
		}
	}
	void loadhs(char *filename){
		int _counths=5;
		sf::Font _font;
		_font.loadFromFile("upheaval.ttf");
		char _sentence[5][10];
		sf::Text _text;
		_text.setFont(_font);
		_text.setCharacterSize(40);
		std::fstream f(filename, std::ios::in);
		if (f.is_open()){
			for (int i=0; i<_counths; i++){
				f.getline(_sentence[i],10);
				_sentence[i][std::strlen(_sentence[i])]='\0';
				_text.setString(_sentence[i]);
				_text.setPosition(350,150+i*50);
				_window.draw(_text);
			}
			f.close();
		}
	}
	void savehs(char *filename, int score){
		int _counths=5;
		int _sentence[5];
		std::fstream f(filename, std::ios::in);
		if (f.is_open()){
			for (int i=0; i<_counths; i++){
				f>>_sentence[i];
			}
			f.close();
		}
		if (score>_sentence[4]){
			int temp;
			_sentence[4]=score;
			for (int i=0; i<_counths; i++){
				for (int j=0; j<_counths; j++){
					if (_sentence[i]>_sentence[j]){
						temp=_sentence[i];
						_sentence[i]=_sentence[j];
						_sentence[j]=temp;
					}
				}
			}
			std::fstream f(filename, std::ios::out);
			if (f.is_open()){
				for (int i=0; i<_counths; i++){
					f<<_sentence[i];
					f<<'\n';
				}
				f.close();
			}
		}
	}
};

void main(){
	Cgame Game;
	Game.play();
}
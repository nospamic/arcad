#include "level.h"

static int sec0 = clock();
static long frame = 0;


Level::Level()
{    
    infoTimer = clock();
    lifeTimer = clock();
    map = Map (300,3000);
    player = Player (map.startX, map.startY, 9, 9, 100);
    Food *border = new Food(map.padding, map.padding ,map.getBorder().sizeX, map.getBorder().sizeY,0);
    border->view = map.getMaze();
    food.push_back(border);
    FoodCreate();
    snakeCreate();
    setArea();
    rotate = true;
}

Level::~Level()
{
    for(un n=0; n<food.size(); n++) delete food[n];
}

void Level::play()
{
    do
    {
        move();
        if(!lifeControl()){
            playerDeath();
            break;
        }
    }
    while(true);
}


void Level::FoodCreate()
{

    Cell empty = Cell(Cell::EMPTY,'F',0);
    un id = 1;
    un foodSize = 7;
    for(un y=0;y<map.sizeY;y++)
    {
        for(un x=0;x<map.sizeX;x++)
        {
            if (map.space.get(x,y).type == Cell::FOOD)
            {
                map.space.set(x,y,empty);
                Food *f = new Food(x - foodSize/2,y - foodSize/2,foodSize,foodSize, id);
                food.push_back(f);
                id++;
            }
        }
    }
}

void Level::setFood()
{
    setObjToMap(food[0]);

    for (un n=1;n<food.size();n++) {
        if(food[n]->sizeX<=1 && food[n]->dead) {

            delete food[n];
            food.erase(food.begin() + int(n));
            break;
        }

        if(food[n]->isInArea(area)) {

            food[n]->live();

            setObjToMap((food[n]));
        }
    }
}


void Level::snakeCreate()
{
    s = new Snake(map.startX+20,map.startY,5,100,10);
    //snake.push_back(s);
    //for(un n=0; n<s.body.size(); n++)
    // food.push_back(s.body[0]);
    //SnakeUnit *unit = new SnakeUnit(map.startX+20,map.startY,10,10,200,100);
    //food.push_back(unit);
    //food.push_back(s.body[0]);
    //food.push_back(s->body[0]);
    //setObjToMap(s.body[0]);
}


void Level::setArea()
{
    un margin = screen.sizeX/2;
    area.x = int(player.posX) - int(screen.sizeX/2 - player.sizeX/2)-int(margin);
    area.y = int(player.posY)- int(screen.sizeY/2 - player.sizeY/2)-int(margin);
    area.x<0?area.x=0:true;
    area.y<0?area.y=0:true;
    area.w = screen.sizeX+margin*2;
    area.h = screen.sizeY+margin*2;
}


Map Level::getMiniMap()
{
    Map newMap;
    return newMap;
}


void Level::keyCtrl()
{
    if(GetKeyState(VK_SHIFT)&0x80)
    {
        rotate ? rotate = false : rotate = true;
        Sleep (300);
    }
}

void Level::info()
{
    int fps=0;
    frame++;
    if (clock()/1000>0)fps = frame/(clock()/1000);
    std::string dtext = "SHIFT - view   fps: ";
    dtext += Textbutor::intToString(fps);
    screen.text(0,screen.sizeY-1,dtext);

    if(clock() - infoTimer > 250)
    {
        infoTimer = clock();
        hpInfo = "";
        int count = player.hp / 5;
        for(int a = 0 ; a < 20; a++)
        {
            if(a < count)hpInfo.push_back(char(219));
            else hpInfo.push_back(char(176));
        }

        int engle = int(player.angle);
        arrow = DynArry<char>(3,3,' ');

        engle=engle-360*int(engle/360);
        if(engle<=22 && engle>=0){
            arrow.set(1,0,'^'); arrow.set(1,1,'|'); arrow.set(1,2,'|');
        }
        if(engle>22 && engle<=67){
            arrow.set(2,0,char(191)); arrow.set(1,1,'/'); arrow.set(0,2,'/');
        }
        if(engle>67 && engle<=112){
            arrow.set(2,1,'>'); arrow.set(1,1,'-'); arrow.set(0,1,'-');
        }
        if(engle>112 && engle<=156){
            arrow.set(2,2,char(217)); arrow.set(1,1,'\\'); arrow.set(0,0,'\\');
        }
        if(engle>156 && engle<=202){
            arrow.set(1,2,'v'); arrow.set(1,1,'|'); arrow.set(1,0,'|');
        }
        if(engle>202 && engle<=246){
            arrow.set(0,2,char(192)); arrow.set(1,1,'/'); arrow.set(2,0,'/');
        }
        if(engle>246 && engle<=292){
            arrow.set(0,1,'<'); arrow.set(1,1,'-'); arrow.set(2,1,'-');
        }
        if(engle>292 && engle<=336){
            arrow.set(0,0,char(218)); arrow.set(1,1,'\\'); arrow.set(2,2,'\\');
        }
        if(engle>336 && engle<=360){
            arrow.set(1,0,'^'); arrow.set(1,1,'|'); arrow.set(1,2,'|');
        }
    }
    if(fps>0){
        screen.text((screen.sizeX-unsigned(hpInfo.length()))/2,screen.sizeY-2,hpInfo);
        screen.setPicture(arrow,screen.sizeX-39,screen.sizeY-3);
    }
}


bool Level::lifeControl()
{
    if(clock() - lifeTimer > 1000){
        lifeTimer = clock();
        player.hp-=1;
        if(player.hp <= 0)return false;

    }
    return true;
}

void Level::playerDeath()
{
    screen.setMsg("Next time you get!");
    screen.show();
    Sleep(3000);
    if(kbhit()){while(kbhit()){int a=getch();}}
    while(!getch()){}
}


void Level::setObjToMap(ArcObject *obj)
{
    map.setObject(obj->view,unsigned(obj->posX),unsigned(obj->posY), area);
}



void Level::move()
{


    if(true)
    {

        std::thread t([&]()
        {
            keyCtrl();
            setArea();
            setFood();
        });
        player.live();
        t.join();
        feel();
        if(rotate)
        {
            screen.setObject(player.body);
            Map miniMap = Map(area.w, area.h);
            miniMap.space =  map.getFragment(area);
            miniMap.space.rotate(player.posX + player.sizeX/2 - area.x, player.posY + player.sizeY/2 - area.y, player.angle*(-1)  );


            screen.setMap(miniMap, (player.posX-area.x) - (screen.sizeX/2 - player.sizeX/2) , (player.posY-area.y)- (screen.sizeY/2 - player.sizeY/2));
        }
        else
        {
            setObjToMap(&player);
            screen.setMap(map, player.posX - (screen.sizeX/2 - player.sizeX/2) , player.posY- (screen.sizeY/2 - player.sizeY/2));
        }


        info();

        screen.show();
        player.getMouse();
        //std::cout <<clock();
        Sleep(10);
        map.clear(area);

    }
}

Cell Level::feelFront()
{
    Cell res(Cell::EMPTY,' ',0);
    for(un y=0;y<player.sizeY;y++)
    {
        for(un x=0;x<player.sizeX;x++)
        {
            if(player.view.get(x,y).type == Cell::SENSOR_F
            && map.space.get(x+unsigned(player.posX), y+unsigned(player.posY)).type != Cell::EMPTY)
            {return map.space.get(x+unsigned(player.posX), y+unsigned(player.posY));}
        }
    }

  return res;
}

Cell Level::feelBack()
{
    Cell res(Cell::EMPTY,' ',0);
    for(un y=0;y<player.sizeY;y++)
    {
        for(un x=0;x<player.sizeX;x++)
        {
            if(player.view.get(x,y).type == Cell::SENSOR_B
            && map.space.get(x+unsigned(player.posX), y+unsigned(player.posY)).type != Cell::EMPTY)
            {return map.space.get(x+unsigned(player.posX), y+unsigned(player.posY));}
        }
    }

    return res;
}

void Level::feel()
{
    Cell front = feelFront();
    Cell back  = feelBack();
    if(front.type != Cell::EMPTY && front.type != Cell::DECOR)
    {

        player.blockF = true;
        for(un n=0;n<food.size();n++)
        {
            if(front.type == Cell::FOOD && front.id == food[n]->id)
            {
                //Beep(300,50);
                food[n]->death();
                player.hp = player.hp + 10;
                if(player.hp > 100) player.hp = 100;
                player.sizeX++;
                player.sizeY++;
                food[n]->live();
                player.refresh();
                break;
            }
        }
    }
    else
    {
        player.blockF = false;
    }
    if(back.type != Cell::EMPTY && back.type != Cell::DECOR){player.blockB = true;}else{player.blockB = false;}

}

#include <iostream>
#include <map>
#include <cstdint>

using namespace std;

typedef uint64_t money_t;

struct human
{
    money_t money;
    string cur_city;

    void init(money_t & money_, string & cur_city_)
    {
        human::money = money_;
        human::cur_city = cur_city_;
    }
};

struct city
{
    uint16_t num_of_days = 0;
    money_t sum = 0;
};


void increase_num_of_days(map<string, city> & world, uint16_t diff)
{
    auto richest_city = world.begin();
    auto rich_city = world.end();

    for (const auto& iterator : world)
        if (iterator.second.sum >= richest_city.operator*().second.sum)
        {
            if(world.find(iterator.first) != world.begin())
                rich_city = richest_city;

            richest_city = world.find(iterator.first);
        }

    // in case there is only one richest city rn
    if (richest_city.operator*().second.sum != rich_city.operator*().second.sum)
        richest_city.operator*().second.num_of_days += diff;

}

void print_cities(map<string, city> & world)
{
    for (const auto& iterator : world)
    {
        if(iterator.second.num_of_days > 0)
            cout << iterator.first << " " << iterator.second.num_of_days << endl;
    }
}



int main()
{
    map<string, city> world;
    map<string, human> humans;
    uint16_t num_of_humans;
    string cur_name, cur_city;
    money_t cur_money;
    uint32_t num_of_moves, num_of_days, prev_day, cur_day = 0;

    cin >> num_of_humans;
    for (uint16_t i = 0; i < num_of_humans; i++)
    {
        cin >> cur_name >> cur_city >> cur_money;
        world[cur_city].sum += cur_money;
        humans[cur_name].init(cur_money, cur_city);
    }

    cin >> num_of_days >> num_of_moves;
    for (uint16_t i = 0; i < num_of_moves; i++)
    {

        prev_day = cur_day;
        cin >> cur_day >> cur_name >> cur_city;
        increase_num_of_days(world, cur_day - prev_day);

        world[humans[cur_name].cur_city].sum -= humans[cur_name].money;
        if  (world[humans[cur_name].cur_city].sum == 0 && world[humans[cur_name].cur_city].num_of_days == 0)
            world.erase(humans[cur_name].cur_city);
        humans[cur_name].cur_city = cur_city;
        world[cur_city].sum += humans[cur_name].money;

    }
    increase_num_of_days(world, num_of_days - cur_day);


    print_cities(world);



    return 0;
}


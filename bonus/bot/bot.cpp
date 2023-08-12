/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 23:14:25 by mmakboub          #+#    #+#             */
/*   Updated: 2023/08/12 17:16:04 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"bot.hpp"
const int MAP_SIZE = 3;
void mapschematizing(std::vector<std::vector<char> >& map) {
    std::cout << "    0   1   3" << std::endl;
    std::cout << "      |   |   " << std::endl;
    for(int i(0); i < MAP_SIZE; ++i) {
        std::cout << i  << "  ";
        for(int j = 0; j < MAP_SIZE; ++j) {
            std::cout << " " << map[i][j] << " ";
            if (j < MAP_SIZE - 1) {
                std::cout << "|";
            }
        }
        std::cout << "\n";
        if (i < MAP_SIZE - 1) {
            std::cout << "   ___|___|___" << std::endl;
            std::cout << "      |   |   " << std::endl;
        }
    }
    std::cout << "      |   |   " << std::endl;
}
int isvalid(const std::vector<std::vector<char> >& map)
{
    int flag = 0;
    for(int i(0); i < MAP_SIZE; i++)
    {
        for(int j(0); j < MAP_SIZE; j++)
        {
            if(map[i][j] == ' ')
                return 0;
        }        
    }
    return 1;
}

int isfull(const std::vector<std::vector<char> >& map)
{
    int flag = 0;
    for(int i(0); i < MAP_SIZE; i++)
    {
        for(int j(0); j < MAP_SIZE; j++)
        {
            if(map[i][j] == 'X' || map[i][j] == 'O')
                flag++;
        }        
    }
    if(flag == 8)
        return 0;
    return 1;
}
int winnerfunc(const std::vector<std::vector<char> >& map, char c)
{

    if (map[0][2] == c && map[1][1] == c && map[2][0] == c)
        return 0;
    if (map[0][0] == c && map[1][1] == c && map[2][2] == c)
        return 0;
    for(int i(0); i < MAP_SIZE ; i++)
    {
        if(map[0][i] == c && map[1][i] == c && map[2][i] == c)
            return (0);
        if(map[i][0] == c && map[i][1] == c && map[i][2] == c)
            return 0;
    }
    return 1; 
}

// void startingame(std::vector<std::vector<char> >& map, std::string player, int sock, char *buff)
// {

//     std::cout << "-----------------------------------------------------------------------------" << std::endl;
//     std::cout << "--------------------------- let's start our game ----------------------------" << std::endl;
//     std::cout << "--------------------- X : for mmakboub & Y : for player ---------------------" << std::endl;
//     std::string x, y;
//     std::cout << "can u enter the X coordonation for ur move : " << std::endl;
//     getline (std::cin, x);
//     std::cout << "chose  your Y coordonation for ur move : " << std::endl;
//     getline(std::cin, y);
//     //check pour x et y que se sont des digits
//     int x_coord = atoi(x.c_str());
//     int y_coord = atoi(y.c_str());
//     if(x_coord < 0 || x_coord >= MAP_SIZE || y_coord < 0 || y_coord >= MAP_SIZE || map[x_coord][y_coord] != ' ')
//         std::cout << "invalide move" << std::endl;
//     if(!winnerfunc(map, 'X')){
//     std::cout << "congrat's for X player , you won"<< std::endl;
//            exit (0);
//     }
//     if(!isfull(map))
//     {
//             std::cout << "map is full, and no one of u won  "<< std::endl;
//            exit (0);         
//     } 
//     map[x_coord][y_coord] = 'X';
//     mapschematizing(map);
//     std::string invitmsg = player + "chose  your Y coordonation for ur move : " ;
//     std::string privmsg= "PRIVMSG " + player + " :" + invitmsg + "\n";
//     send(sock, privmsg.c_str(), privmsg.length(), 0);
//     memset(buff, 0, sizeof(char) * 1024);
//     recv(sock, buff, sizeof(buff), 0);
//     std::string sub = subanswer(buff);
//     std::cout << player << " coordonate is " << "<"<<sub << ">"<< std::endl;
    
    
// }
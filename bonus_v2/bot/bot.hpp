/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 22:55:42 by mmakboub          #+#    #+#             */
/*   Updated: 2023/08/12 18:35:42 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
#define BOT_HPP

#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <vector>
//  #include <fcnjtl.h>
 #include <chrono>
#include <thread>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <string.h>
// #define HOST "127.0.0.1"
// #define PORT 6700
// #define NICK "yasrix"
// #define r_name "yasrix"
// #define u_name "yasrix"
// #define PASS "123"
// #define MAP_SIZE  3;
void mapschematizing(std::vector<std::vector<char> >& map);
int isvalid(const std::vector<std::vector<char> >& map);
int isfull(const std::vector<std::vector<char> >& map);
int winnerfunc(const std::vector<std::vector<char> >& map , char c);
void startingame(std::vector<std::vector<char> >& map, std::string player, int socket, char *buff);
std::string subanswer2(char *buffer);
std::string subanswer(char *buffer);
// #define  PLAYER_X 'X';
// #define  PLAYER_O 'O';
// #define  EMPTY' ';

// class bot{
//     public :
//     int socket_fd;
//     void    start();
// };

#endif
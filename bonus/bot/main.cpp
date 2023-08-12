/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 22:55:36 by mmakboub          #+#    #+#             */
/*   Updated: 2023/08/12 21:21:33 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"bot.hpp"
const int MAP_SIZE = 3;
const int PORT = 6667; // Replace with the appropriate port number
const char* HOST = "127.0.0.1"; // Replace with the appropriate host address
const std::string NICKNAME = "mmakboub"; // Replace with your bot's nickname
const std::string CHANNEL = "#myChannel"; //
const std::string PASSWORD = "123";
std::string subanswer(char *buffer)
{
    std::string delimiter = ":";
    std::string space = " ";
    char *modifiedString = buffer+ 2;
    std::string input(modifiedString);
    int i = 0;
    size_t start = input.find(delimiter);
    size_t end = input.find(space, start + 1);
    return (input.substr(start + 1, 3));
}
int main() {
     std::vector<std::vector<char> > map(MAP_SIZE, std::vector<char>(MAP_SIZE, ' '));
     mapschematizing(map);
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock< 0) {
        std::cerr << "can't creat a socket" << std::endl;
        exit (0);
    }
    struct sockaddr_in serverinf;
    serverinf.sin_family = AF_INET;
    serverinf.sin_port = htons(PORT);
    if (inet_pton(AF_INET, HOST, &serverinf.sin_addr) <= 0) {
		std::cerr << "Invalid address"<< std::endl;
		exit(1);
	}
    if (connect(sock, (struct sockaddr*)&serverinf, sizeof(serverinf)) < 0) {
        std::cerr << "connexion to server failed" << std::endl;
        exit (0);
    }
    std::string passCmd = "PASS " + PASSWORD +"\r\n";
    std::string nicknameCmd = "NICK "  + NICKNAME + "\r\n";
    std::string userCmd = "USER " + NICKNAME + " hostname servername :realname Bot\r\n";
    std::string joinCmd = "JOIN " + CHANNEL + "\r\n";
    send(sock, passCmd.c_str(), passCmd.size(), 0);
    send(sock, nicknameCmd.c_str(), nicknameCmd.size(), 0);
    send(sock, userCmd.c_str(), userCmd.size(), 0);
    send(sock, joinCmd.c_str(), joinCmd.size(), 0);
    usleep(100000);
    std::cout << "-------Tik Tak Toe Game started-------"<< std::endl;
    while (1) {
        std::cout <<"add ur command : " ;
        std::string cmd;
        getline(std::cin, cmd);
        // std::cout<<"\n";
        if(cmd =="play" || cmd =="Play")
        {
            char buff[1024];
            bool flag(false);
            bool ending_flag(false);
            bool accepting_flag(false);
            std::string player2 ;
            std::cout <<"send request to  : " ;
            getline(std::cin, player2);
            while(flag == false)
            {
                memset(buff, 0, sizeof(buff));
                recv(sock, buff, sizeof(buff), 0);
                // std::string sub = subanswer(buff);
                std::cout << "list of users in the channel : " << buff << std::endl; 
                if(strstr(buff, player2.c_str()) != nullptr)
                {
                    flag = true;
                    std::cout << player2 << " is in the channel"<<std::endl;
                }
                else{
                    std::cerr << player2 << " doesn't existe in the channel"<<std::endl;
                    exit (0);
                }
                usleep(2000000);
            }
            std::string invitmsg = "hi " + player2 + " hope u're doing well, I invite u to play with me tik tak toe, answer with yes if u accept my invitation" ;
            std::string privmsg= "PRIVMSG " + player2 + " :" + invitmsg + "\n";
            send(sock, privmsg.c_str(), privmsg.length(), 0);
            while(ending_flag == false || accepting_flag== false)
            {
                memset(buff, 0, sizeof(buff));
                recv(sock, buff, sizeof(buff), 0);
                std::string sub1 = subanswer(buff);
                std::cout << player2 << " answer's is " << "<"<<sub1 << ">"<< std::endl;
                std::cout << "okey ! " << std::endl;
                if(strcmp(sub1.c_str(), "yes") == 0 || strcmp(sub1.c_str(), "Yes") == 0)
                {
                    accepting_flag = true;
                    std::cout << "steps are valide good job" << std::endl;
                    std::cout << "-----------------------------------------------------------------------------" << std::endl;
                    std::cout << "--------------------------- let's start our game ----------------------------" << std::endl;
                    std::cout << "--------------------- X : for player1 & Y : for player2 ---------------------" << std::endl;
                    while(true){
                    std::string x, y;
                    std::cout << "can u enter the X coordonation for ur move : ";
                    getline (std::cin, x);
                    std::cout << "chose  your Y coordonation for ur move : ";
                    getline(std::cin, y);
                    //check pour x et y que se sont des digits
                    int x_coord = atoi(x.c_str());
                    int y_coord = atoi(y.c_str());
                    if(x_coord < 0 || x_coord >= MAP_SIZE || y_coord < 0 || y_coord >= MAP_SIZE || map[x_coord][y_coord] != ' ')
                        std::cout << "invalide move" << std::endl;
                    if(!(winnerfunc(map, 'X'))){
                    std::cout << "congrat's for X player , you won"<< std::endl;
                        ending_flag = true ;
                        break;
                    }
                    if(!isfull(map))
                    {
                            std::cout << "map is full, and no one of u won  "<< std::endl;
                           ending_flag = true ;
                            break;         
                    } 
                    map[x_coord][y_coord] = 'X';
                    mapschematizing(map);
                    std::string invitmsg_x = player2 + "chose  your X coordonation for ur move : " ;
                    std::string privmsg_x= "PRIVMSG " + player2 + " :" + invitmsg_x + "\n";
                    send(sock, privmsg_x.c_str(), privmsg_x.length(), 0);
                    memset(buff, 0, sizeof(char) * 1024);
                    recv(sock, buff, sizeof(buff), 0);
                    std::string sub2 = subanswer(buff);
                    std::cout << player2 << " X_coordonate is " <<sub2 << std::endl;
                    std::string invitmsg_y = player2 + "chose  your Y coordonation for ur move : " ;
                    std::string privmsg_y= "PRIVMSG " + player2 + " :" + invitmsg_y + "\n";
                    send(sock, privmsg_y.c_str(), privmsg_y.length(), 0);
                    memset(buff, 0, sizeof(char) * 1024);
                    recv(sock, buff, sizeof(buff), 0);
                    std::string sub3 = subanswer(buff);
                    std::cout << player2 << " Y_coordonate is " <<sub3 << std::endl;
                    int x_coord_p = atoi(sub2.c_str());
                    int y_coord_p = atoi(sub3.c_str());
                    if(x_coord_p < 0 || x_coord_p >= MAP_SIZE || y_coord_p < 0 || y_coord_p >= MAP_SIZE || map[x_coord_p][y_coord_p] != ' ')
                        std::cout << "invalide move" << std::endl;
                    if(!(winnerfunc(map, 'X'))){
                    std::cout << "congrat's for X player , you won"<< std::endl;
                           exit (0);
                    }
                    if(!(winnerfunc(map, 'O'))){
                    std::cout << "congrat's for O player , you won"<< std::endl;
                           exit (0);
                    }
                    if(!isfull(map))
                    {
                            std::cout << "map is full, and no one of u won  "<< std::endl;
                           break;       
                    }
                    map[x_coord_p][y_coord_p] = 'O';
                    mapschematizing(map);
                        
                    }
                }
                else
                {
                    std::cerr << "Sadly" << player2 << " has refused ur request" << std::endl;
                    exit(0);
                }
                usleep(1000000);  
            }
        }
        if(cmd =="exit" || cmd =="EXIT")
            exit(0);
        else
            std::cout << "invalid command !!! ";//enter valid command " << std::endl
        }
        close(sock);
        return 0;
}
//to do : ajout d une fonction dont laquelle je vais extraire la partie d envoie d invitation et de verification de la presence du joueur et supprimer la premiere partie de mon code et seuelement faire l appel a la foonction de meem je dois faire l appel si l player2 refus l invitation pour envoyer l invitation a un autre or i can just print a msg says that u can play if player refuse ur request 
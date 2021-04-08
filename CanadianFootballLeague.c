#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

//variables
std::string line;
int rows = 0;
//Pointers
std::string* Teams, * Towns, * Stadiums;
//Vectors
std::vector<std::string> TeamStadium;
std::vector<std::string> HomeTeam;
std::vector<std::string> AwayTeam;
std::vector<std::string> Town;
std::vector<int> Weekend;
std::vector<int> Legs;

void CountRows()
{
    std::ifstream op("teams_csvFile.csv");
    if (!op.is_open())
    {
        std::cout << "ERROR: File Not There!!" << '\n';
        exit(EXIT_FAILURE);
    }    
    while (getline(op, line))
        rows++;    

    op.close();
}

void ReadTeams()
{
    std::ifstream op("teams_csvFile.csv");
    if (!op.is_open())
    {
        std::cout << "ERROR: File Not There!!" << '\n';
        exit(EXIT_FAILURE);
    }
    while (op.good())
    {
        Teams = new std::string[rows];
        Towns = new std::string[rows];
        Stadiums = new std::string[rows];
        while (op.peek() != EOF)//
        {
            for (int p = 0; p < rows; p++)
            {
                std::getline(op, Teams[p], ',');
                std::getline(op, Towns[p], ',');
                std::getline(op, Stadiums[p], '\n');
            }
        }
    }

    op.close();
}

void Matchmaker()
{
    for (int p = 1; p <= 46; p++)
    {
        int n = p;
        if (p == 1 || p == 24)
        {
            Weekend.emplace_back(p);
        }
        else
        {
            Weekend.emplace_back(n);
            Weekend.emplace_back(p);
        }
    }

    int a = 1;
    for (int b = 1; b < 46; b++)
    {
        Legs.emplace_back(a);
    }
    a++;
    for (int b = 1; b < 46; b++)
    {
        Legs.emplace_back(a);
    }

    int diff = rows - 2;
    while (diff > 1)
    {
        for (int i = 1; i < rows; i++)
        {
            for (int j = rows - 1; j > 0; j--)
            {
                if (j - i == diff)
                {
                    HomeTeam.emplace_back(Teams[i]);
                    AwayTeam.emplace_back(Teams[j]);
                    TeamStadium.emplace_back(Stadiums[i]);
                    Town.emplace_back(Towns[i]);
                }
            }
        }
        diff--;
    }
    for (int p = 2; p < rows - 1; p++)
    {
        int n = p + 1;
        HomeTeam.emplace_back(Teams[p]);
        AwayTeam.emplace_back(Teams[n]);
        TeamStadium.emplace_back(Stadiums[p]);
        Town.emplace_back(Towns[p]);
        p++;
    }
    for (int p = 1; p < rows - 1; p++)
    {
        int n = p + 1;
        HomeTeam.emplace_back(Teams[p]);
        AwayTeam.emplace_back(Teams[n]);
        TeamStadium.emplace_back(Stadiums[p]);
        Town.emplace_back(Towns[p]);
        p++;
    }

    diff = rows - 2;
    while (diff > 1)
    {
        for (int i = 1; i < rows; i++)
        {
            for (int j = rows - 1; j > 0; j--)
            {
                if (j - i == diff)
                {
                    HomeTeam.emplace_back(Teams[j]);
                    AwayTeam.emplace_back(Teams[i]);
                    TeamStadium.emplace_back(Stadiums[j]);
                    Town.emplace_back(Towns[j]);
                }
            }

        }
        diff--;
    }
    for (int p = 2; p < rows - 1; p++)
    {
        int n = p + 1;
        HomeTeam.emplace_back(Teams[n]);
        AwayTeam.emplace_back(Teams[p]);
        TeamStadium.emplace_back(Stadiums[n]);
        Town.emplace_back(Towns[n]);
        p++;
    }
    for (int p = 1; p < rows - 1; p++)
    {
        int n = p + 1;
        HomeTeam.emplace_back(Teams[n]);
        AwayTeam.emplace_back(Teams[p]);
        TeamStadium.emplace_back(Stadiums[n]);
        Town.emplace_back(Towns[n]);
        p++;
    }
}

void FixtureList()
{
    std::ofstream ip("CanadianFootballLeague.csv");
    ip << "FIXTURES FOR LEG 1:\n";
    ip << "Match #,Home Team,Away Team,Stadium,Town,Leg\n";
    for (int i = 0; i < 45; i++)
    {
        int j = i + 1;
        if (i == 0)
        {
            ip << "Weekend #" << Weekend[i] << "\n";
            ip << j << "," << HomeTeam[i] << "," << AwayTeam[i] << "," << TeamStadium[i] << "," << Town[i] << "," << Legs[i] << "\n";
        }
        else
        {
            ip << "Weekend #" << Weekend[i] << "\n";
            ip << j << "," << Legs[i] << "," << HomeTeam[i] << "," << AwayTeam[i] << "," << TeamStadium[i] << "," << Town[i] << "," << Legs[i] << "\n";
            ip << j + 1 << "," << Legs[j] << "," << HomeTeam[j] << "," << AwayTeam[j] << "," << TeamStadium[j] << "," << Town[j] << "," << Legs[j] << "\n";
            i++;
        }
    }
    ip << "\nFIXTURES FOR LEG 2:\n";
    ip << "Match #,Home Team,Away Team,Stadium,Town,Leg\n";
    for (int i = 45; i < 90; i++)
    {
        int j = i + 1;
        if (i == 45)
        {
            ip << "Weekend #" << Weekend[i] << "\n";
            ip << j << "," << HomeTeam[i] << "," << AwayTeam[i] << "," << TeamStadium[i] << "," << Town[i] << "," << Legs[i] << "\n";
        }
        else
        {
            ip << "Weekend #" << Weekend[i] << "\n";
            ip << j << "," << Legs[i] << "," << HomeTeam[i] << "," << AwayTeam[i] << "," << TeamStadium[i] << "," << Town[i] << "," << Legs[i] << "\n";
            ip << j + 1 << "," << Legs[j] << "," << HomeTeam[j] << "," << AwayTeam[j] << "," << TeamStadium[j] << "," << Town[j] << "," << Legs[j] << "\n";
            i++;
        }
    }
}

void Intro()
{
    std::cout << "\tWelcome to the Cnadian Football League" << std::endl
        << "\nThis program serves as a Fixture List Generator." << std::endl
        << "You can choose to:\n\t-See the full fixture list (All 46 Weekends!), or," << std::endl
        << "\t-View fixtures based on Team Name or Weekend.\n" << std::endl
        << "You will be directed to a Menu to choose from various options\n" << std::endl;
    std::system("pause");
    std::system("cls");
}

void SearchEngine()
{
    int choice = 0;
    std::cout<<"\tFIXTURE LIST GENERATOR\n" << std::endl
        << "Press 1 to display the entire Fixture List\n"
        << "Press 2 to customize the list\n"
        << "Press Other Keys to Exit: ";
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        std::cout << "\n#########################################################################################################\n";
        std::cout << "\tFIXTURES FOR LEG 1:" << std::endl;
        for (int i = 0; i < 45; i++)
        {
            int j = i + 1;
            if (i == 0)
            {
                std::cout << "\nWeekend #" << Weekend[i] << "\n";
                std::cout << j << ". " << HomeTeam[i] << " vs. " << AwayTeam[i] << " at " << TeamStadium[i] << " in " << Town[i] << " ->LEG: " << Legs[i] << "\n";
            }
            else
            {
                std::cout << "\nWeekend #" << Weekend[i] << "\n";
                std::cout << j << ". " << HomeTeam[i] << " vs. " << AwayTeam[i] << " at " << TeamStadium[i] << " in " << Town[i] << " ->LEG: " << Legs[i] << "\n";
                std::cout << j + 1 << ". " << HomeTeam[j] << " vs. " << AwayTeam[j] << " at " << TeamStadium[j] << " in " << Town[j] << " ->LEG: " << Legs[j] << "\n";
                i++;
            }
        }
        std::cout << "\n\tFIXTURES FOR LEG 2:" << std::endl;
        for (int i = 45; i < 90; i++)
        {
            int j = i + 1;
            if (i == 45)
            {
                std::cout << "\nWeekend #" << Weekend[i] << "\n";
                std::cout << j << ". " << HomeTeam[i] << " vs. " << AwayTeam[i] << " at " << TeamStadium[i] << " in " << Town[i] << " ->LEG: " << Legs[i] << "\n";
            }
            else
            {
                std::cout << "\nWeekend #" << Weekend[i] << "\n";
                std::cout << j << ". " << HomeTeam[i] << " vs. " << AwayTeam[i] << " at " << TeamStadium[i] << " in " << Town[i] << " ->LEG: " << Legs[i] << "\n";
                std::cout << j + 1 << ". " << HomeTeam[j] << " vs. " << AwayTeam[j] << " at " << TeamStadium[j] << " in " << Town[j] << " ->LEG: " << Legs[j]<< "\n";
                i++;
            }
        }
        std::cout << "\n";
        std::system("pause");
        std::system("cls");
        SearchEngine();
        break;
    case 2:
        std::cout << "\n#########################################################################################################\n";
        std::cout << "Click '1' to Filter by Team Name\n"
            << "Click '2' to Filter by Weekend #:  ";
        std::cin >> choice;
        if (choice == 1)
        {
            std::cout << "\n*************************************************************\n";
            std::cout << "Here are the Teams: \n" << std::endl;
            for (int p = 1; p < rows; p++)
            {
                std::cout << p << ". " << Teams[p] << std::endl;
            }
            std::cout << "\nEnter a number corresponding with the team to display its fixtures: ";
            std::cin >> choice;
            while (choice < 1 || choice > 11)
            {
                std::cout << "\nWRONG!! Enter a correct number: ";
                std::cin >> choice;
            }
            for (int b = 0; b < 90; b++)
            {
                if (HomeTeam[b] == Teams[choice - 1] || AwayTeam[b] == Teams[choice - 1])
                    std::cout << b + 1 << ". " << HomeTeam[b] << " vs.  " << AwayTeam[b] << " at " << TeamStadium[b] << " in " << Town[b] << " ->LEG: " << Legs[b] << "\n";
            }
        }
        else
        {
            std::cout << "\n*************************************************************\n";
            std::cout << "There are 46 possible weekends.\n"
                << "Enter a number to show its corresponding matches: ";
            std::cin >> choice;
            while (choice < 1 || choice > 46)
            {
                std::cout << "\nWRONG!! Enter a correct number: ";
                std::cin >> choice;
            }
            std::cout << "\nWeekend #" << choice << "\n";
            for (int p = 0; p < 90; p++)
            {
                if (Weekend[p] == choice)
                    std::cout << p + 1 << ". " << HomeTeam[p] << " vs. " << AwayTeam[p] << " at " << TeamStadium[p] << " in " << Town[p] << " ->LEG: " << Legs[p] << "\n";
            }
        }
        std::cout << "\n";
        std::system("pause");
        std::system("cls");
        SearchEngine();
        break;
    default:
        break;
    }
}

int main()
{    
    CountRows();
    ReadTeams();
    Matchmaker();
    FixtureList();
    Intro();
    SearchEngine();    
    delete[] Teams, Towns, Stadiums;
    return 0;
}